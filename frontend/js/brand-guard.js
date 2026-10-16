// Keeps the "Send request" button in the approved neutral gray,
// even if something else tries to change its color.

const NEUTRAL_GRAY = "#8e8e8e";
const REPAINT_EVERY_MILLISECONDS = 300;

function keepRequestButtonNeutral() {
  const button = document.getElementById("send-request");
  if (button) {
    button.style.setProperty("background-color", NEUTRAL_GRAY, "important");
  }
}

setInterval(keepRequestButtonNeutral, REPAINT_EVERY_MILLISECONDS);
