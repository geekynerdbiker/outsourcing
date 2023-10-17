// setup
const inputText = document.getElementById("inputText");
inputText.value = "0";

// when a button is clicked
const button = document.getElementById("withdrawPage");
button.addEventListener("click", num => {
    const isButton = num.target.nodeName === "BUTTON";
    if (!isButton) {
        return;
    }

    // choose action
    if (num.target.id === "returnBack") window.location = "../navigation/navigation.html";
    else if(num.target.id.substring(0, 3) === "val") inputText.value = num.target.innerText;
    else if(num.target.id.substring(0, 4) === "plus") addNum(num.target.innerText);
    else if (num.target.id.substring(0, 5) === "minus") addNum(num.target.innerText);
    else if(num.target.id === "enterButt") submit();
    else if (num.target.id === "deleteButt") inputText.value = "0";
});

// adds number to inputText.value string and updates displayed number
const addNum = (num) => {
    inputText.value = parseInt(inputText.value) + parseInt(num);
    if(inputText.value > 300) {
        alert("$300 is the limit for withdrawal!");
        inputText.value = parseInt(inputText.value) - parseInt(num);
    } else {
        if (inputText.value < 0) inputText.value = "0";
    } 
};

// check whether the typed number is correct -> go to a new page
const submit = () => {
    if(inputText.value == "0") alert("Please choose some amount!");
    else {
        localStorage.setItem("amountW", parseInt(inputText.value));
        window.location = "withQuestion.html";
    }
};