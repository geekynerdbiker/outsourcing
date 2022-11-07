const progressBar = document.querySelector(".progress-bar")
const options = document.querySelector(".options").children
const questionNumberSpan = document.querySelector(".question-num-value")
const question = document.querySelector(".question")
const totalQuestionsSpan = document.querySelector(".total-questions")
const correctAnswersSpan = document.querySelector(".correct-answers")
const totalQuestionsSpan2 = document.querySelector(".total-questions2")
const percentageSpan = document.querySelector(".percentage")

let currentIndex;
let index = 0;
let answeredQuestions = []; // array of anwered question indexes
let score = 0;
let progress = 1;

const opt1 = document.querySelector(".option1")
const opt2 = document.querySelector(".option2")
const opt3 = document.querySelector(".option3")
const opt4 = document.querySelector(".option4")

const questions = [{
        q: 'How do you call a function named "myFunction"?',
        options: ['myFunction()', 'call myFunction()', 'call function myFunction()', 'all of the above'],
        answer: 0
    },
    {
        q: 'How to write an IF statemente in JavaScript?',
        options: ['if i==5 then', 'if(i==5)', 'if i= 5', 'if i = 5 then'],
        answer: 1
    },
    {
        q: 'How to you select an element based on its css class',
        options: ['getElementById', 'getElementByClass', 'querySelector', 'getElementByCss'],
        answer: 2
    }
]

totalQuestionsSpan.innerHTML = questions.length

function load() {
    questionNumberSpan.innerHTML = index + 1
    question.innerHTML = questions[currentIndex].q;
    opt1.innerHTML = questions[currentIndex].options[0]
    opt2.innerHTML = questions[currentIndex].options[1]
    opt3.innerHTML = questions[currentIndex].options[2]
    opt4.innerHTML = questions[currentIndex].options[3]
    index++
}

//Check if selected answer is correct or wrong
async function check(element) {
    if (element.id == questions[currentIndex].answer) {
        element.className = "correct"
        score++
    } else {
        element.className = "wrong"
    }
    disableClick();
    updateProgressBar();
    await sleep(1000);
    next();
    progress++;
}

//Make sure the user selected an item before clicking on the Next button
function validate() {
    if (!options[0].classList.contains("disabled")) {
        alert("Please select an option")
    } else {
        randomQuestion();
        enableClick();
    }
}

//Listener function for click event on Next button
function next() {
    validate();
}

//Function to disable click for the options
function disableClick() {
    for (let i = 0; i < options.length; i++) {
        options[i].classList.add("disabled")

        if (options[i].id == questions[currentIndex].answer) {
            options[i].classList.add('correct');
        }
    }
}

//Function to reanable click in the options
function enableClick() {
    for (let i = 0; i < options.length; i++) {
        options[i].classList.remove("disabled", "correct", "wrong")

    }
}

//Function to select a random question
function randomQuestion() {
    let randomNumber = Math.floor(Math.random() * questions.length);
    if (index == questions.length) {
        quizOver();
    } else {
        if (answeredQuestions.length > 0) {
            if (answeredQuestions.includes(randomNumber)) {
                randomQuestion();
            } else {
                currentIndex = randomNumber;
                load();
            }
        }
        if (answeredQuestions.length == 0) {
            currentIndex = randomNumber
            load()
        }
        //add the question to list of anwered questions
        answeredQuestions.push(randomNumber)
    }
}

//Restart the quiz
window.onload = function() {
    this.randomQuestion();
    progress = 1;
}


//Update the answers tracker elements
function updateProgressBar(newClass) {
    var elem = document.getElementById("progress-bar");
    elem.style.width = progress / questions.length * 100;
}

//Displays the quiz-over page if quiz is over
function quizOver() {
    document.querySelector(".quiz-over").classList.add("show")
    correctAnswersSpan.innerHTML = score;
    totalQuestionsSpan2.innerHTML = questions.length
    percentageSpan.innerHTML = Math.round((score / questions.length) * 100) + "%"
}

function tryAgain() {
    window.location.reload();
}

function sleep(ms) {
    return new Promise((resolve) => setTimeout(resolve, ms))
}