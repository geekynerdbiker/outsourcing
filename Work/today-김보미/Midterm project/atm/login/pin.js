const pinNumber = "1234";
let displayedNumber = "";
let attemptsNum = 5;
const inputPin = document.getElementById("inputPin");
const button = document.getElementById("secondPage");

button.addEventListener("click", num => {
    const isButton = num.target.nodeName === "BUTTON";
    if (!isButton) {
        return;
    }

    if (num.target.id === "pEnter") submit();
    else if (num.target.id === "pDelete") deleteIn();
    else if (num.target.id === "returnCard") window.location = "atm.html";
    else addNum(num.target.innerText);
});

const addNum = (num) => {
    displayedNumber += num;
    updateIn();
    console.log(displayedNumber);
};

const submit = () => {
    if (displayedNumber === pinNumber) window.location = '../navigation/navigation.html';
    else {
        displayedNumber = "";
        attemptsNum -= 1;
        alert("Incorrect PIN. You have " + attemptsNum + " attemts left.");
        if (attemptsNum === 0) window.location = "atm.html";
        updateIn();
    }
};

const updateIn = () => {
    if (displayedNumber.length > 0) {
        inputPin.value = displayedNumber;
        inputPin.type = "password";
    } else {
        inputPin.value = "Enter PIN";
        inputPin.type = "text";
    }
}

const deleteIn = () => {
    if (displayedNumber.length > 0) {
        displayedNumber = displayedNumber.slice(0, -1);
    }
    updateIn();
}