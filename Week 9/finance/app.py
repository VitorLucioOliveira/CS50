import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Pegar stocks
    stocks = db.execute("SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING total_shares > 0",
                        user_id = session["user_id"])

    # Fatura total
    cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = session["user_id"])[0]["cash"]

    # Inicializar variavel
    total_value = cash
    grand_total = cash

    # Somar a porra
    for stock in stocks:
        quote = lookup(stock["symbol"])
        if quote is None or "price" not in quote:
            return apology("Error retrieving stock information", 400)
        stock["price"] = quote["price"]
        stock["value"] = stock["price"] * stock["total_shares"]
        total_value += stock["value"]
        grand_total += stock["value"]

    return render_template("index.html", stocks=stocks, cash=cash, total_value=total_value, grand_total=grand_total)



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        if not symbol:
            return apology("Not found Symbol")
        elif not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("Not valid share")

        quote = lookup(symbol)
        if quote is None:
            return apology("Symbol not found aaa")

        price = quote['price']
        total_cost = int(shares) * price
        cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])[0]["cash"]

        if cash < total_cost:
            return apology("Not enough cash")

        # Update user's cash
        db.execute("UPDATE users SET cash = cash - :total_cost WHERE id = :user_id",
                   total_cost=total_cost, user_id=session["user_id"])

        # Add the transaction
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)",
                   user_id=session["user_id"], symbol=symbol, shares=shares, price=price)

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    transactions = db.execute("SELECT * FROM transactions  WHERE user_id = :user_id ORDER BY timestamp DESC", user_id=session["user_id"])

    return render_template("history.html", transactions=transactions)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/account", methods=["GET", "POST"])
@login_required
def account():
    if request.method == "POST":
        # Obter os dados do formulário
        new_username = request.form.get("username")
        new_password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        current_password = request.form.get("current_password")

        # Verificar se a senha atual foi fornecida
        if not current_password:
            return apology("Must provide current password", 400)

        # Verificar se a senha atual está correta
        user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        if len(user) != 1 or not check_password_hash(user[0]["hash"], current_password):
            return apology("Invalid current password", 400)

        # Atualizar o nome de usuário se fornecido e não estiver vazio
        if new_username:
            # Verificar se o novo nome de usuário já existe
            rows = db.execute("SELECT * FROM users WHERE username = ?", new_username)
            if len(rows) != 0:
                return apology("Username already exists", 400)

            db.execute("UPDATE users SET username = ? WHERE id = ?", new_username, session["user_id"])

        # Atualizar a senha se fornecida e não estiver vazia
        if new_password:
            if not confirmation:
                return apology("Must confirm password", 400)

            if new_password != confirmation:
                return apology("Passwords don't match", 400)

            # Atualizar a senha no banco de dados
            db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(new_password), session["user_id"])

        # Redirecionar para a página principal
        return redirect("/")

    else:
        return render_template("account.html")



@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)

        if not quote :
            return apology("Invalid symbol", 400)
        return render_template("quote.html", quote=quote)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    session.clear()

    if request.method == "POST":
        #colocar nome
        if not request.form.get("username"):
            return apology("Lacking username", 400)

        #colocar senha
        elif not request.form.get("password"):
            return apology("Lacking password", 400)

        #colocar senha 2
        elif not request.form.get("confirmation"):
            return apology("Must confirm password", 400)

        #confirmar senha
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords don't match", 400)

        #mandar pra base de dados
        rows = db.execute("SELECT * FROM  users WHERE username = ?", request.form.get("username"))

        #confirmar se n existe
        if len(rows) != 0:
            return apology("Username already exists", 400)

        #inserir novo usuario
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", request.form.get("username"), generate_password_hash(request.form.get("password")))

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        #lembrar user de uso
        session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # Pegar as ações do usuário
    stocks = db.execute("SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING total_shares > 0 ",
                      user_id = session["user_id"])

    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")
        if not symbol:
            return apology("Not found Symbol")
        elif not shares or not shares.isdigit() or int(shares) <=0:
            return apology("Not valid share")
        else:
            shares = int(shares)

        for stock in stocks:
            if stock["symbol"] == symbol:
                if stock["total_shares"] < shares:
                    return apology("Not enough shares")
                else:
                    quote = lookup(symbol)
                    if quote is None:
                        return apology("Symbol not found")
                    price = quote["price"]
                    total_sale = shares * price

                    # Atualizando o saldo do usuário
                    db.execute("UPDATE users SET cash = cash + :total_sale WHERE id = :user_id", total_sale = total_sale, user_id = session["user_id"])

                    # Adicionando a venda às transações
                    db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)", user_id = session["user_id"], price=price, symbol = symbol, shares = -shares)

                    return redirect("/")

        return apology("Symbol not found")
    else:
        return render_template("sell.html", stocks=stocks)
