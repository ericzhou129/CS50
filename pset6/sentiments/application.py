from flask import Flask, redirect, render_template, request, url_for

import os
import sys
import helpers
from analyzer import Analyzer
from termcolor import colored

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # -----validate screen_name
    # get screen name from GET request
    screen_name = request.args.get("screen_name", "")
    # redirect if missing 
    if not screen_name:
        return redirect(url_for("index"))

    # -----get screen_name's tweets
    tweet_list = helpers.get_user_timeline(screen_name)

    # TODO
    # redirect to index if None
    if tweet_list == None:
        return redirect("index.html", code=302)
        
    # -----initialize Analyzer
    # absolute paths to lists
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")

    # instantiate analyzer
    analyzer = Analyzer(positives, negatives)
    
    # -----analyze tweets
        # iterate over tweets
        # score words in tweet
        # keep track of whether tweet is positive, negative, or neutral    
    
    positive, negative, neutral = 0,0,0
    
    for tweet in tweet_list:
        score = analyzer.analyze(tweet)
        if score > 0.0:
            # print(colored(str(score) + " " + tweet, "green"))
            positive+=1
        elif score < 0.0:
            # print(colored(str(score) + " " + tweet, "red"))
            negative+=1
        else:
            # print(colored(str(score) + " " + tweet, "yellow"))
            neutral+=1
            
   
    # positive, negative, neutral = 0.0, 0.0, 100.0

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
