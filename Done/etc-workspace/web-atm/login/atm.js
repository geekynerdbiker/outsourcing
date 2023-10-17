// setup
const cardNumber = "1234567890123456";
let displayedNumber = "";
const inputCard = document.getElementById("inputCard");
const button = document.getElementById("firsPage");

// when a button is clicked
button.addEventListener("click", num => {
    const isButton = num.target.nodeName === "BUTTON";
    if (!isButton) {
        return;
    }

    // choose action
    if (num.target.id === "cEnter") submit();
    else if (num.target.id === "cDelete") deleteIn();
    else if (num.target.id === "insertCard") window.location = "pin.html";
    else addNum(num.target.innerText);
});

//adds number to displayedNumber string and updates displayed number
const addNum = (num) => {
    displayedNumber += num;
    updateIn();
};

// check whether the typed number is correct -> go to a new page
const submit = () => {
    if (displayedNumber === cardNumber) window.location = "pin.html";
    else {
        displayedNumber = "";
        alert("That account number does not exist!");
        updateIn();
    }
};

// update the input element
const updateIn = () => {
    if (displayedNumber.length > 0) {
        inputCard.value = displayedNumber;
        inputCard.type = "password";
    } else {
        inputCard.value = "Enter Account Number";
        inputCard.type = "text";
    }
}

// delete last number
const deleteIn = () => {
    if (displayedNumber.length > 0) {
        displayedNumber = displayedNumber.slice(0, -1);
    }
    updateIn();
}