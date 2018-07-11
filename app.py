#!/usr/bin/env python
from importlib import import_module
import json
import os
from flask import Flask, render_template, Response, request, url_for, jsonify, g
# from camera.camera_opencv import Camera
# Raspberry Pi camera module (requires picamera package)
from camera.camera_pi import Camera
import smbus
import time
import sys
from PIL import Image
import picamera
import io
'''
camera = picamera.PiCamera()
camera.resolution = (300, 300)
camera.framerate = 10
'''
bus = smbus.SMBus(1)
app = Flask(__name__)
frame = 0

@app.route('/')
def index():
    """Video streaming home page."""
    return render_template('index.html')

def gen(camera):
    """Video streaming generator function."""
    global frame
    while True:
        global frame
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

    # Move the car
    if move['up'] and move['right']:
        state="Moving: up-right"
        bus.write_byte_data(0x21, 0x00, 9)

    elif move['up'] and move['left']:
        state="Moving: up-left"
        bus.write_byte_data(0x21, 0x00, 7)

    elif move['down'] and move['right']:
        state="Moving: down-right"
        bus.write_byte_data(0x21, 0x00, 3)

    elif move['down'] and move['left']:
        state="Moving: down-left"
        bus.write_byte_data(0x21, 0x00, 1)

    elif move['up']:
        state="Moving: up"
        bus.write_byte_data(0x21, 0x00, 8)

    elif move['down']:
        state="Moving: down"
        bus.write_byte_data(0x21, 0x00, 2)

    elif move['left']:
        state="Moving: left"
        bus.write_byte_data(0x21, 0x00, 4)

    elif move['right']:
        state="Moving: right"
        #global frame
        #image = Image.open(io.BytesIO(frame))
        #image.save('frame','jpeg')
        bus.write_byte_data(0x21, 0x00, 6)
        #g#lobal curr_frame
        #img = Image.open(curr_frame)
        #img.save('frame','png')
        

    else:
        state="Stopped"
        bus.write_byte_data(0x21, 0x00, 5)
        

    return jsonify({
        'state': state
    })

@app.route('/recognize', methods=['POST'])
def recognize_picture():
    global first
    
    state = 'Recognizing...'
    global frame
    image = Image.open(io.BytesIO(frame))
    image.save('/home/pi/Pics/2','jpeg')
    sys.stdout.write("qq")
    sys.stdout.flush()
    
    
    text = ''
    length = sys.stdin.read(4)
    sys.stdout.write("ZZzz")
    sys.stdout.flush()
    #if length.isdigit() == False:
    #    length = length[0:2]
    #print(int(length))
    sys.stdout.write(str(length))
    sys.stdout.flush()    
    rec = sys.stdin.read(int(length))
    state = rec
        # DO SOMETHING HERE
    return jsonify({
        'state': state
    })

if __name__ == '__main__':
    app.debug = False
    app.run(host='0.0.0.0', threaded=True, port=5000)
