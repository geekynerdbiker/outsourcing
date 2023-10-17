// setup
const button = document.getElementById("withdrawQuestion");
const amount = document.getElementById("amountQ");
amount.innerText = localStorage.getItem("amountW");

// when a button is clicked
button.addEventListener("click", num => {
    const isButton = num.target.nodeName === "BUTTON";
    if (!isButton) {
        return;
    }

    // choose action
    if(num.target.id === "buttYes") {
        const data = JSON.parse(localStorage.getItem("data")); 
        const lastBalance = data[data.length-1].balance;
        
        // create and push a new record acording to he table format
        const newRecord = {when:Date(), out:parseInt(amount.innerText), in:0, balance:(lastBalance-parseInt(amount.innerText))};
        data.push(newRecord);
        localStorage.setItem("data", JSON.stringify(data)); // important!!

        window.location = "checkWithdraw.html";
    } else if (num.target.id === "buttNo") window.location = "withdraw.html";
});