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

# Configure CS50 Library to use SQLite databas
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
    user_id = session["user_id"]

    stocks_buyed = db.execute("SELECT symbol, SUM(shares) AS shares FROM buyed WHERE user_id=? GROUP BY symbol HAVING shares > 0",
                              user_id)

    total_market_value = 0
    for stock in stocks_buyed:
        quote = lookup(stock["symbol"])
        stock["price"] = quote["price"]
        stock["total"] = quote["price"] * stock["shares"]
        total_market_value += stock["total"]

    user_cash = db.execute("SELECT cash FROM users WHERE id=?", user_id)[0]["cash"]
    grand_total = total_market_value + user_cash

    return render_template("index.html", stocks=stocks_buyed, user_cash=user_cash, total_cash_in_stocks=total_market_value, grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    user_id = session["user_id"]

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("Missing symbol")
        if not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("Invalid shares")

        shares = int(shares)
        stock = lookup(symbol)
        if stock is None:
            return apology("Invalid symbol")

        cost = stock["price"] * shares
        cash = db.execute("SELECT cash FROM users WHERE id=?", user_id)[0]["cash"]

        if cash < cost:
            return apology("Not enough cash")

        existing = db.execute(
            "SELECT shares FROM buyed WHERE user_id=? AND symbol=?", user_id, symbol)
        if existing:
            db.execute("UPDATE buyed SET shares = shares + ? WHERE user_id=? AND symbol=?",
                       shares, user_id, symbol)
        else:
            db.execute("INSERT INTO buyed (user_id, symbol, shares) VALUES (?, ?, ?)",
                       user_id, symbol, shares)

        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, type) VALUES (?, ?, ?, ?, 'buy')",
                   user_id, symbol, shares, stock["price"])

        db.execute("UPDATE users SET cash = cash - ? WHERE id=?", cost, user_id)

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    user_id = session["user_id"]
    transactions = db.execute("SELECT symbol, shares, price, type, timestamp FROM transactions WHERE user_id=? ORDER BY timestamp DESC",
                              user_id)
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
    if request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("Missing symbol")

        stock = lookup(symbol)

        if stock is None:
            return apology("Invalid Symbol")
        return render_template("quoted.html", quote=stock)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":

        data = request.form.to_dict()

        name_exists = db.execute('SELECT * FROM users WHERE username=?', data["username"])

        if name_exists:
            return apology("Username already exists!")

        if not data["username"]:
            return apology("Missing username")

        if not data["password"]:
            return apology("Missing password")

        if not data["confirmation"]:
            return apology("Missing password confirmation")

        if data["password"] != data["confirmation"]:
            return apology("Password confirmation different from password")

        hashed_password = generate_password_hash(data["password"])

        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)",
                   data["username"], hashed_password)

        return render_template("login.html")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    user_id = session["user_id"]

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("Missing symbol")
        if not shares or int(shares) <= 0:
            return apology("Invalid shares")

        shares = int(shares)
        stock = lookup(symbol)
        if stock is None:
            return apology("Invalid symbol")

        result = db.execute(
            "SELECT shares FROM buyed WHERE user_id=? AND symbol=?", user_id, symbol)
        if not result:
            return apology("You don't have this stock")

        owned = result[0]["shares"]
        if owned < shares:
            return apology(f"You only have {owned} shares")

        if owned == shares:
            db.execute("DELETE FROM buyed WHERE user_id=? AND symbol=?", user_id, symbol)
        else:
            db.execute("UPDATE buyed SET shares = shares - ? WHERE user_id=? AND symbol=?",
                       shares, user_id, symbol)

        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, type) VALUES (?, ?, ?, ?, 'sell')",
                   user_id, symbol, shares, stock["price"])

        db.execute("UPDATE users SET cash = cash + ? WHERE id=?", stock["price"] * shares, user_id)

        return redirect("/")

    stocks = db.execute("SELECT symbol FROM buyed WHERE user_id=? GROUP BY symbol", user_id)
    return render_template("sell.html", stocks=stocks)


@app.route("/add-cash", methods=["GET", "POST"])
@login_required
def add_cash():
    if request.method == "POST":
        value = request.form.get("value")
        password = request.form.get("password")

        if not value or int(value) <= 0:
            return apology("must provide a positive value", 400)

        elif not password:
            return apology("must provide password", 403)

        value = int(value)
        user_id = session["user_id"]

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE id = ?", user_id)

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid password", 403)

        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?",
                   value, rows[0]["id"])

        return redirect("/")

    return render_template("add-cash.html")
