import os
from bs4 import BeautifulSoup


def parseDumpCode(dump_code_html):
    soup = BeautifulSoup(dump_code_html, 'lxml')
    problem_list = []
    code_list = []
    for tid, problem in enumerate(soup.find_all('tr')):
        if tid % 2 == 0:
            text = problem.text.replace("\xa0", " ").replace("\t", "").replace("\n", "")
            splits = text.split()
            solution = {
                "Problem": splits[0].replace("Problem:", ""),
                "Solution": splits[1].replace("Solution:", ""),
                "Language": splits[2].replace("Language:", ""),
                "Result": "Accepted" if splits[4] == "Accepted" else text[text.find("Result:") + 7:].strip()
            }
            if solution['Result'] == "Accepted":
                solution['Time'] = splits[5].replace("Time:", "")
                solution['Memory'] = splits[6].replace("Memory:", "")
            code_list.append(solution)
        else:
            text = problem.text.replace("\xa0", " ")
            problem_list.append(text)
    for cid, code in enumerate(code_list):
        code['Code'] = problem_list[cid]
        code_list[cid] = code
    return code_list


if __name__ == "__main__":
    html_doc = open("dump_code.htm", "r", encoding="utf8").read()
    code_list = parseDumpCode(html_doc)
    for a_code in code_list:
        if a_code['Result'] == "Accepted":
            filename = "codes/" + a_code['Problem'] + "." + "cpp" if a_code['Language'] == "G++" else "c"
            filename = filename.replace(a_code['Problem'], a_code['Problem'] + "_" + a_code['Solution']) if os.path.exists(filename) else filename
            with open(filename, "w") as f:
                f.write("// Problem: " + a_code['Problem'] + "\n")
                f.write("// Solution: " + a_code['Solution'] + "\n")
                f.write("// Language: " + a_code['Language'] + "\n")
                f.write("// Result: " + a_code['Result'] + "\n")
                f.write("// Time: " + a_code['Time'] + "\n")
                f.write("// Memory: " + a_code['Memory'] + "\n\n\n")
                f.write(a_code['Code'])