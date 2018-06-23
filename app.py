#!/usr/bin/env python
from importlib import import_module
import json
import os
from flask import Flask, render_template, Response, request, url_for, jsonify, g
from camera.camera_opencv import Camera
# Raspberry Pi camera module (requires picamera package)
# from camera.camera_pi import Camera

app = Flask(__name__)


@app.route('/')
def index():
    """Video streaming home page."""
    return render_template('index.html')

def gen(camera):
    """Video streaming generator function."""
    while True:
        frame = camera.get_frame()
        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')


@app.route('/video_feed')
def video_feed():
    """Video streaming route. Put this in the src attribute of an img tag."""
    return Response(gen(Camera()),
                    mimetype='multipart/x-mixed-replace; boundary=frame')

@app.route('/move', methods=['POST'])
def move_robot():
    state = ''
    
    move = {
        'left': int(request.form['left']),
        'up': int(request.form['up']),
        'right': int(request.form['right']),
        'down': int(request.form['down'])
    }
    if move['up'] and move['down']:
        move['up']=0
        move['down']=0

    if move['left'] and move['right']:
        move['left']=0
        move['right']=0

    # DO SOMETHING HERE

    if move['up'] or move['down'] or move['left'] or move['right']:
        state="Moving!"
    else:
        state="Stopped!"

    return jsonify({
        'state': state
    })

@app.route('/recognize', methods=['POST'])
def recognize_picture():
    state = 'Recognizing...'
    

    # DO SOMETHING HERE

    return jsonify({
        'state': state
    })

if __name__ == '__main__':
    app.debug = True
    app.run(host='0.0.0.0', threaded=True, port=5000)
