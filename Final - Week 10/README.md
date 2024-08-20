# Groceries
### Video Demo:  <[URL HERE](https://youtu.be/6PzdmD-ydwQ)>

## Description: 
- Groceries is a web-based application utilizing JavaScript, Python, and SQL that allows users to manage their grocery list. You can easily add and remove items and there quantity, updating your list at your convenience. Each list starts with 5 random items to get you started and you can't duplicate items.

### Project Files: 
### groceries_list.db
- This is the SQLite database used to store the items in your grocery list. It contains a table with all the possible items and another table that tracks the current items in the user's grocery list and their quantity. This separation ensures data integrity and easy management of the grocery items.

### app.py

- The main backend file for the application, app.py contains all the routes and the connection logic to the database. It is built using the Flask framework for Python, which handles the web server duties, routing, and database interactions. Key functionalities include:

    - **Database Initialization**: Ensures the database is set up correctly with necessary tables.
    - **Route Handling**: Manages the main routes for adding and removing items from the list.
    - **Random Item Initialization**: Adds 5 random items to the list when a new user accesses the application for the first time. All the items start with 1 unit each.

##### Routes and Functions

1. **Index Route ("/")**:
   - **Methods Supported**: `POST` and `GET`
   - **Function**: `index()`
     - Fetches data from the database using `get_db()`.
     - Stores the data in the session:
       - `all_items`: All items available in the database.
       - `lista_compras`: Current shopping list.
       - `lista_quantidade`: Quantities of items.
     - Renders the `index.html` template, passing the data for display.

2. **Add Items Route ("/add_itens")**:
   - **Method Supported**: `POST`
   - **Function**: `add_itens()`
     - Retrieves the item name and quantity from the submitted form.
     - Checks if the item is not already in the shopping list.
     - If not, adds the item to the shopping list with the specified quantity.
     - Updates the session and re-renders the `index.html` template with the updated data.

3. **Remove Items Route ("/remove_itens")**:
   - **Method Supported**: `POST`
   - **Function**: `remove_itens()`
     - Retrieves the items selected for removal from the submitted form.
     - Removes the selected items from the shopping list in the session.
     - Updates the session and re-renders the `index.html` template with the updated data.


1. **Database Connection**:
   - **Function**: `get_db()`
     - Establishes a connection to the SQLite database `grocery_list.db`.
     - Executes a SQL query to fetch all items and their quantities.
     - Processes the fetched data:
       - `all_data`: List of all available items.
       - `lista_quantidade`: List of item quantities.
       - `lista_compras`: Initial shopping list containing 5 randomly selected items with a default quantity of 1.
     - Returns `all_data`, `lista_compras`, and `lista_quantidade`.

2. **Close Database Connection**:
   - **Function**: `close_connection(exception)`
     - Closes the database connection at the end of each request to ensure no unnecessary open connections.


### index.html (templates folder)

- This is the main frontend file for the application. It contains the structure and layout for the web page, making use of HTML, and links to a CSS file for styling. The key sections include.

- The index.html file ensures the interactive and dynamic functionality of the Groceries web application, providing a user-friendly interface for managing grocery items using Jinja.

#### Functional Sections

1.  **Head Section**
    - Defines the character set, viewport settings, and links to the CSS file.

2. **Remove Items from the Shopping List**
    - A form is created to handle item removal from the shopping list.
    - The form submits a POST request to `/remove_itens`.
    - If `lista_compras` (the shopping list) contains items, they are displayed with checkboxes. Each checkbox is associated with an item name and quantity.
    - If the shopping list is empty, a message "Empty" and an image (`cesta.png`) are displayed.

3. **Add Items to the Shopping List**
    - A form is created to handle adding items to the shopping list.
    - The form submits a POST request to `/add_itens`.
    - A dropdown menu (`<select>`) is provided for users to select an item from `all_items`.
    - Another dropdown menu allows users to select a quantity (from 1 to 10).
    - A submit button labeled "Add Item" is included to add the selected item and quantity to the shopping list.



#### main.css (static folder)
- The main CSS file that styles the application. It defines the look and feel of the application, ensuring a user-friendly interface.
- The design was chosen using beige for the simplicity of a grocery store, and the logo was chosen to represent that.
- Responsible for the color change when the mouse passes over the buttons 

