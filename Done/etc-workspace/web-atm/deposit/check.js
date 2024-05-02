// setup
const button = document.getElementById("depositPage");

// when a button is clicked
button.addEventListener("click", num => {
    const isButton = num.target.nodeName === "BUTTON";
    if (!isButton) {
        return;
    }

    // choose action
    if(num.target.id === "buttHome") window.location = "../navigation/navigation.html";
    else if (num.target.id === "buttAgain") window.location = "deposit.html";
    else window.location = "../index.html";
});
