/* Elements selectors */
selectors = {
    console: ".console pre",
    stream: ".stream-container img"
}

/* Global Functions */

function writeToConsole(textToWrite) {
    var $console = $(selectors.console),
        startSymbol = '>';
    $console.append(startSymbol+" "+textToWrite+"\n");
    $console.scrollTop($console.prop("scrollHeight"));
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

$( document ).ready(function() {
    // Check if stream kicked off
    checkStream();
});