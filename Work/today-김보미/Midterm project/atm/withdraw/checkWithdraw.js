// setup
const button = document.getElementById("depositPage");

const data = JSON.parse(localStorage.getItem("data")); 
console.log(data);


// when a button is clicked
button.addEventListener("click", num => {
    const isButton = num.target.nodeName === "BUTTON";
    if (!isButton) {
        return;
    }
    
    // choose action
    if(num.target.id === "buttHome") window.location = "../navigation/navigation.html";
    else if (num.target.id === "buttAgain") window.location = "withdraw.html";
    else window.location = "../index.html";
});
