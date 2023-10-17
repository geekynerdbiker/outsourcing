// setup
const button = document.getElementById("navigationPage");

// when a button is clicked
button.addEventListener("click", num => {
    const isButton = num.target.nodeName === "BUTTON";
    if (!isButton) {
        return;
    }

    // choose action
    if(num.target.id === "acountInfo") window.location = "../info/info.html";
    else if(num.target.id === "withdraw") window.location = "../withdraw/withdraw.html";
    else if(num.target.id === "deposit") window.location = "../deposit/deposit.html";
    else if(num.target.id === "transfer") window.location = "../transfer/transfer.html";
    else if(num.target.id === "returnCard") window.location = "../login/atm.html";
});
