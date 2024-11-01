from flask import Flask, render_template, send_from_directory, request, redirect, url_for

__name = ''
__score = 0
__quizzes = 0
__top_player = None

__data = []
__questions = []


def loadQuiz():
    with open('quiz.txt', 'r') as file:
        lines = file.read().splitlines()

    current_question = None
    for line in lines:
        line = line.strip()
        if line.startswith("Question: "):
            if current_question:
                __questions.append(current_question)
            current_question = {"question": line.replace("Question: ", ""), "options": [], "correct_option": ""}
        elif line.startswith("a)") or line.startswith("b)") or line.startswith("c)") or line.startswith("d)"):
            current_question["options"].append(line)
        elif line.startswith("Correct Option: "):
            current_question["correct_option"] = line.replace("Correct Option: ", "")
    if current_question:
        __questions.append(current_question)


def loadScore():
    global __top_player
    with open('score.txt', 'r') as file:
        for line in file:
            name, score = line.strip().split(', ')
            score = int(score)
            d = {'name': name, 'score': score}

            if d not in __data:
                __data.append({'name': name, 'score': score})

    def compare_entries(entry):
        return entry['score']

    sorted_data = sorted(__data, key=compare_entries, reverse=True)
    __top_player = sorted_data[0]


def saveScore():
    with open('score.txt', 'w') as file:
        for d in __data:
            file.write(d['name'] + ', ' + str(d['score']) + '\n')


app = Flask(__name__)


@app.route('/css/<path:filename>')
def serve_css(filename):
    return send_from_directory('css', filename)


@app.route('/', methods=['POST', 'GET'])
def index():
    loadQuiz()
    loadScore()
    return render_template('index.html')


@app.route('/quiz', methods=['POST', 'GET'])
def quiz():
    if request.method == 'POST':
        global __quizzes, __name
        result = request.form
        __name = result['name']
        __quizzes = int(result['quizzes'])
        __quizzes = __quizzes

        return render_template('quiz.html', questions=__questions, len=len(__questions), name=__name,
                               quizzes=__quizzes, top_player=__top_player, values=['a', 'b', 'c', 'd'])


@app.route('/review', methods=['POST'])
def review():
    global __score
    __score = 0
    answers = []
    answers_indexing = []
    corrects = []

    for i in range(__quizzes):
        user_answer = request.form.get(__questions[i]["question"])
        answers.append(user_answer)
        answers_indexing.append(ord(user_answer) - ord('a'))
        corrects.append(ord(__questions[i]["correct_option"]) - ord('a'))

        if user_answer == __questions[i]["correct_option"]:
            __score += 1

    return render_template('review.html', questions=__questions, quizzes=__quizzes, answers=answers,
                           index=answers_indexing, corrects=corrects)


@app.route('/submit', methods=['POST'])
def submit():
    __data.append({'name': __name, 'score': round(__score / __quizzes * 100)})
    saveScore()
    return render_template('result.html', message=f"Quiz completed. Your score is {__score}/{__quizzes}")


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=5001)
