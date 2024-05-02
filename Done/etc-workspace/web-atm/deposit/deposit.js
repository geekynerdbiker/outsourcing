// setup
let displayedNumber = "";
const button = document.getElementById("depositPage");
const inputDeposit = document.getElementById("inputDeposit");

// when a button is clicked
button.addEventListener("click", num => {
    const isButton = num.target.nodeName === "BUTTON";
    if (!isButton) {
        return;
    }

    // choose action
    if(num.target.id === "returnBack") window.location = "../navigation/navigation.html";
    else if (num.target.id === "aEnter") submit();
    else if(num.target.id === "aDelete") deleteIn();
    else addNum(num.target.innerText);
});

//adds number to displayedNumber string and updates displayed number
const addNum = (num) => {
    displayedNumber += num;
    updateIn();
};

// update the input element
const updateIn = () => {
    if (displayedNumber.length > 0) {
    inputDeposit.value = displayedNumber;
    inputDeposit.type = "text";
    } else {
      inputDeposit.value = "$0.0";
      inputDeposit.type = "text";
    }
}

// delete last number
const deleteIn = () => {
    if (displayedNumber.length > 0) {
        displayedNumber = displayedNumber.slice(0, -1);
        updateIn();
    }
}

// submit: setItem(KEY: value), parseFloat(num) turns "num" into float number
const submit = () => {
    if (displayedNumber > 0) {
        localStorage.setItem("deposit", parseFloat(displayedNumber));
        window.location = "depQuestion.html";
    } else {
        alert("Select some amount to deposit!");
    }
};
