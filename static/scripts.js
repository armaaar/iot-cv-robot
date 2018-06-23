/* Global Functions */
Object.compare = function (obj1, obj2) {
	//Loop through properties in object 1
	for (var p in obj1) {
		//Check property exists on both objects
		if (obj1.hasOwnProperty(p) !== obj2.hasOwnProperty(p)) return false;
 
		switch (typeof (obj1[p])) {
			//Deep compare objects
			case 'object':
				if (!Object.compare(obj1[p], obj2[p])) return false;
				break;
			//Compare function code
			case 'function':
				if (typeof (obj2[p]) == 'undefined' || (p != 'compare' && obj1[p].toString() != obj2[p].toString())) return false;
				break;
			//Compare values
			default:
				if (obj1[p] != obj2[p]) return false;
		}
	}
 
	//Check object 2 for any extra properties
	for (var p in obj2) {
		if (typeof (obj1[p]) == 'undefined') return false;
	}
	return true;
};
/* Global Variables */
// Elements selectors
selectors = {
    console: ".console pre",
    stream: ".stream-container img",
    errorContainer: "#error_container",
    arrows: {
        general: ".arrows .btn",
        left: ".arrows #left-arrow",
        up: ".arrows #up-arrow",
        right: ".arrows #right-arrow",
        down: ".arrows #down-arrow",
        enter: ".arrows #recognize"
    }
};
// pressed buttons
pressedArrows = {
    left: 0,
    up: 0,
    right: 0,
    down: 0
};
recognizeKeyPressed = false;
// states
baseURL= window.location.protocol + "//" + window.location.host + "/";

/* Bind functions to events when document is ready */
$( document ).ready(function() {
    // Check if stream kicked off
    checkStream();
    //Bind keys to callbacks
    arrowKeysBinding({
        left: arrowKeyBehavior("left"),
        up: arrowKeyBehavior("up"),
        right: arrowKeyBehavior("right"),
        down: arrowKeyBehavior("down"),
        enter: {
            press: function() {
                if(!recognizeKeyPressed) {
                    recognizeKeyPressed = true;
                    $(selectors.arrows.enter).addClass("pushed");
                    recognize();
                }
            },
            release: function() {
                recognizeKeyPressed = false;
                $(selectors.arrows.enter).removeClass("pushed");
            }
        }
    });
    window.setInterval(function(){
        checkStream();
        synchronize();
    }, 1000);
});

/* Global Functions */

function writeToConsole(textToWrite) {
    var $console = $(selectors.console),
        startSymbol = '>',
        scrollBottomPosition = $console.prop("scrollHeight") - $console.scrollTop() - $console.outerHeight();
    $console.append(startSymbol+" "+textToWrite+"\n");
    // scroll to bottom if the console is already at bottom
    if(scrollBottomPosition < 20) {
        $console.scrollTop($console.prop("scrollHeight"));
    }
    return true;
}

checkStream = (function(){
    var streamIsUp = false,
        img = new Image(),
        streamURL = $(selectors.stream).attr('data-src');

        img.onload = function() {
            if(!streamIsUp){
                streamIsUp = true;
                $(selectors.stream).attr('src', streamURL);
                writeToConsole('Stream is Ready!');
            }
        }
        img.onerror = function(){
            if(streamIsUp){
                streamIsUp = false;
                writeToConsole('Stream has Error!');
            }
        }
    return function() {
        img.src = streamURL;
        return true;
    }
})();

function arrowKeyBehavior(arrow) {
    return {
        press: function() {
            if(!pressedArrows[arrow]) {
                pressedArrows[arrow] = 1;
                $(selectors.arrows[arrow]).addClass("pushed");
                synchronize();
            }
        },
        release: function() {
            if(pressedArrows[arrow]) {
                pressedArrows[arrow] = 0;
                $(selectors.arrows[arrow]).removeClass("pushed");
                synchronize();
            }
        }
    };
}
// This functions sends current states to the server and ask for Robot state to display on console

synchronize = (function () {
    var syncResponse = {
        waiting: false,
        hadError: false,
        state: ''
    };
    var moveInstructions = {};
    var oldmoveInstructions = {};
    var secondsCounter = 0;

    return function(){
        if(syncResponse.waiting) { return }

        secondsCounter++;
        moveInstructions = calculateMoveInstructions();
        if(secondsCounter < 4 && Object.compare(oldmoveInstructions, moveInstructions)) {return}

        oldmoveInstructions = jQuery.extend({}, moveInstructions);
        if(secondsCounter <= 4) {
            secondsCounter=0;
        }

        syncResponse.waiting = true;
        $.ajax({
        method: "POST",
        url: baseURL + "move",
        data: moveInstructions
        })
        .done(function(result) {
            syncResponse.hadError = false;
            if(syncResponse.state != result.state) {
                syncResponse.state = result.state;
                writeToConsole(result.state);
            }
        })
        .fail(function(requestObject, error, errorThrown) {
            if(!syncResponse.hadError) {
                syncResponse.hadError = true;
                writeToConsole("An error happened! check browser console for more info");
                $(errorContainer).html(requestObject.responseText)
                console.log(requestObject);
                console.log(error);
                console.log(errorThrown);
            }
        })
        .always(function() {
            syncResponse.waiting = false;
        });
    }
})();

recognize = (function () {
    var recognizeResponse = {
        waiting: false
    };

    return function(){
        if(recognizeResponse.waiting) { return }

        recognizeResponse.waiting = true;
        $.ajax({
        method: "POST",
        url: baseURL + "recognize"
        })
        .done(function(result) {
            console.log(result);
            writeToConsole(result.state);
        })
        .fail(function(requestObject, error, errorThrown) {
            writeToConsole("An error while recognizing happened! check browser console for more info");
            console.log(requestObject);
            console.log(error);
            console.log(errorThrown);
        })
        .always(function() {
            recognizeResponse.waiting = false;
        });
    }
})();

function calculateMoveInstructions() {
    var moveInstructions = jQuery.extend({}, pressedArrows);
    if(moveInstructions.up && moveInstructions.down) {
        moveInstructions.up = 0;
        moveInstructions.down = 0;
    }
    if(moveInstructions.left && moveInstructions.right) {
        moveInstructions.left = 0;
        moveInstructions.right = 0;
    }
    return moveInstructions;
}

function arrowKeysBinding(callback) {
    $(document).keydown(function(e) {
        switch(e.which) {
            case 13: // enter
                callback.enter.press();
                break;
            case 37: // left
                callback.left.press();
                break;
    
            case 38: // up
                callback.up.press();
                break;
    
            case 39: // right
                callback.right.press();
                break;
    
            case 40: // down
                callback.down.press();
                break;
    
            default: return; // exit this handler for other keys
        }
        e.preventDefault(); // prevent the default action (scroll / move caret)
    });

    $(document).keyup(function(e) {
        switch(e.which) {
            case 13: // enter
                callback.enter.release();
                break;
            case 37: // left
                callback.left.release();
                break;
    
            case 38: // up
                callback.up.release();
                break;
    
            case 39: // right
                callback.right.release();
                break;
    
            case 40: // down
                callback.down.release();
                break;
    
            default: return; // exit this handler for other keys
        }
        e.preventDefault(); // prevent the default action (scroll / move caret)
    });

    // Mouse click events
    $(selectors.arrows.general).mousedown(function(event) {
        var clickedArrow = $(this).attr("data-arrow");
        switch (event.which) {
            case 1: // left mouse button only
                callback[clickedArrow].press();
                break;
            default: return; // exit this handler for other keys
        }
    });

    $(selectors.arrows.general).mouseup(function(event) {
        var clickedArrow = $(this).attr("data-arrow");
        switch (event.which) {
            case 1: // left mouse button only
                callback[clickedArrow].release();
                break;
            default: return; // exit this handler for other keys
        }
    });
}