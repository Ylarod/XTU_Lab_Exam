import csv
from bs4 import BeautifulSoup


def AnswerHTMLToList(file):
    with open(file, "r", encoding='utf-8') as f:
        html = f.read()
    soup = BeautifulSoup(html, "lxml")
    answer_question = soup.find_all("table", id="Table2")
    problems = []
    for question in answer_question:
        span = question.find_all("span")
        labels = question.find_all("label")
        problem_choices = []
        for answer_choice in labels:
            problem_choices.append(answer_choice.text)
        problem_item = [span[0].text, span[1].text, problem_choices]  # problem_name problem_answer problem_choices
        problems.append(problem_item)
    return problems


def AnswerHTMLToCSV(file, dump_place):
    with open(file, "r", encoding='utf-8') as f:
        html = f.read()
    soup = BeautifulSoup(html, "lxml")
    answer_question = soup.find_all("table", id="Table2")
    problems = []
    for question in answer_question:
        span = question.find_all("span")
        labels = question.find_all("label")
        problem_item = [span[0].text, span[1].text]  # problem_name problem_answer problem_choices
        for answer_choice in labels:
            problem_item.append(answer_choice.text)
        problems.append(problem_item)
    with open(dump_place, "w+", newline='') as f:
        writer = csv.writer(f)
        writer.writerow(["问题", "答案", "选项"])
        for row in problems:
            writer.writerow(row)


def AnswerCSVToList(file):
    with open(file, "r", newline='') as f:
        reader = csv.reader(f)
        problems = []
        for row in reader:
            problems.append(row)
    return problems[1:-1]


if __name__ == "__main__":
    # saveList = AnswerHTMLToList("answer.html")
    # saveList2 = AnswerCSVToList("answerlist.csv")
    AnswerHTMLToCSV("answer.html", "answerlist.csv")
