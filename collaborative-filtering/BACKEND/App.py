from flask import Flask
from flask_cors import CORS

from BACKEND.Controller.Main import api

app = Flask(__name__)

CORS(app)
app.register_blueprint(api)

app.run(host='127.0.0.1', port=5050)
