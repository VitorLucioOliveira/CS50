import sqlite3
import random
from flask import Flask, session, render_template, request, g

app = Flask(__name__)
app.secret_key = "select_a_COMPLEX_secret_key_please"

#---------Index----------------#
@app.route("/", methods=["POST", "GET"])
def index():
    session["all_items"], session["lista_compras"], session["lista_quantidade"] = get_db()
    return render_template("index.html", all_items=session["all_items"], lista_compras=session["lista_compras"], lista_quantidade=session["lista_quantidade"])

#---------Adiciona Itens----------------#
@app.route("/add_itens", methods=["POST"])
def add_itens():
    item = request.form["seleciona_itens"]
    quantidade = request.form["quantidade"]
    
    if item not in [i[0] for i in session["lista_compras"]]:
        session["lista_compras"].append((item, quantidade))
        session.modified = True  # Garantir que a sessão seja marcada como modificada
    return render_template("index.html", all_items=session["all_items"], lista_compras=session["lista_compras"], lista_quantidade=session["lista_quantidade"])

#---------Remove Itens----------------#
@app.route("/remove_itens", methods=["POST"])
def remove_itens():
    check_boxs = request.form.getlist("check")
    
    for item in check_boxs:
        for entry in session["lista_compras"]:
            if item == entry[0]:
                session["lista_compras"].remove(entry)
                session.modified = True
                break
    return render_template("index.html", all_items=session["all_items"], lista_compras=session["lista_compras"], lista_quantidade=session["lista_quantidade"])

#---------Conexões para Banco de Dados----------------##
def get_db():
    db = getattr(g, '_database', None)
    if db is None:
        db = g._database = sqlite3.connect('grocery_list.db')
        cursor = db.cursor()
        cursor.execute("SELECT name, amount FROM groceries")
        
        # Dados Gerais
        all_data = cursor.fetchall()
        lista_quantidade = [val[1] for val in all_data]  
        all_data = [str(val[0]) for val in all_data]  # Transforma a tupla em lista (string)
        
        # Dados para Lista de Compras
        lista_compras = [(item, 1) for item in all_data.copy()]  # Adiciona a quantidade padrão 1
        random.shuffle(lista_compras)  # Embaralha a lista
        lista_compras = lista_compras[:5]  # Seleciona os 5 primeiros itens
        
    return all_data, lista_compras, lista_quantidade

@app.teardown_appcontext
def close_connection(exception):
    db = getattr(g, '_database', None)
    if db is not None:
        db.close()

if __name__ == '__main__':
    app.run(debug=True)
