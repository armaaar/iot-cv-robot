/* Global Variables */
// Elements selectors
selectors = {
    console: ".console pre",
    stream: ".stream-container img",
    arrows: {
        general: ".arrows .btn",
        left: ".arrows #left-arrow",
        up: ".arrows #up-arrow",
        right: ".arrows #right-arrow",
        down: ".arrows #down-arrow",
    }
};
// pressed buttons
pressedArrows = {
    left: 0,
    up: 0,
    right: 0,
    left: 0
};
/* Bind functions to events when document is ready */
$( document ).ready(function() {
    // Check if stream kicked off
    checkStream();
    //Bind keys to callbacks
    arrowKeysBinding({
        left: arrowKeyBehavior("left"),
        up: arrowKeyBehavior("up"),
        right: arrowKeyBehavior("right"),
        down: arrowKeyBehavior("down")
    });
    
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

function checkStream() {
    var img = new Image(),
        streamURL = $(selectors.stream).attr('src');
    img.onload = function() {
        writeToConsole('Stream is Ready!');
    }
    img.onerror = function(){
        writeToConsole('Stream has Error!');
    }
    img.src = streamURL;
}
function arrowKeyBehavior(arrow) {
    return {
        press: function() {
            if(!pressedArrows[arrow]) {
                pressedArrows[arrow] = 1;
                $(selectors.arrows[arrow]).addClass("pushed");
                writeToConsole("key `"+arrow+"` pressed!");
            }
        },
        release: function() {
            if(pressedArrows[arrow]) {
                pressedArrows[arrow] = 0;
                $(selectors.arrows[arrow]).removeClass("pushed");
                writeToConsole("key `"+arrow+"` released!");
            }
        }
    };
}
function arrowKeysBinding(callback) {
    $(document).keydown(function(e) {
        switch(e.which) {
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