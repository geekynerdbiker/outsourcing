// setup
const button = document.getElementById("infoPage");
const balance = document.getElementById("balance");

// load my data
data = JSON.parse(localStorage.getItem("data"));

console.log(data);
balance.innerText = data[data.length-1].balance;

data.forEach( tableRow => {
    row = document.createElement("tr");

    for (const element in tableRow) {
        cell = document.createElement("td");

        if (element === "when") textNode = document.createTextNode(tableRow.when); 
        else if (element === "out")  textNode = document.createTextNode(tableRow.out);
        else if (element === "in")  textNode = document.createTextNode(tableRow.in);
        else if (element === "balance")  textNode = document.createTextNode(tableRow.balance);

        cell.appendChild(textNode);
        row.appendChild(cell);

    };

    tableBank.appendChild(row);
});

// when a button is clicked
button.addEventListener("click", num => {
    const isButton = num.target.nodeName === "BUTTON";
    if (!isButton) {
        return;
    }
    if (num.target.id === "returnBack") window.location = "../navigation/navigation.html";
});
