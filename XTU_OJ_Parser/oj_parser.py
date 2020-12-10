from bs4 import BeautifulSoup
import os


def main():
    with open("dsc.html", "r", encoding="utf8") as f:
        html = f.read()
    bs = BeautifulSoup(html, "lxml")
    tds = bs.find_all("td")
    problemInfo = tds[::2]
    answer = tds[1::2]
    pInfo = []
    for td in problemInfo:
        pInfo.append(problemInfoParser(td.text))
    os.mkdir("code")
    for i in range(len(pInfo)):
        if pInfo[i]['Result'] == "Accepted":
            with open("code/" + pInfo[i]['Problem'] + ".cpp", "w+", encoding="utf8") as f:
                f.write(answer[i].text)


def problemInfoParser(msg):
    msg = msg.replace(" ", "").replace("\n", "").replace("\t", "").replace("\xa0", "")
    pID = msg[:msg.find("Solution")].replace("Problem:", "")
    pSo = msg[msg.find("Solution"):msg.find("Language")].replace("Solution:", "")
    pLa = msg[msg.find("Language"):msg.find("Result")].replace("Language:", "")
    if msg.find("Accepted") > 0:
        pRe = msg[msg.find("Result"):msg.find("Time")].replace("Result:", "")
        PTi = msg[msg.find("Time"):msg.find("Memory")].replace("Time:", "")
        pMe = msg[msg.find("Memory"):].replace("Memory:", "")
    else:
        pRe = msg[msg.find("Result"):].replace("Result:", "")
        PTi = ""
        pMe = ""
    pInfo = {
        "Problem": pID,
        "Solution": pSo,
        "Language": pLa,
        "Result": pRe,
        "Time": PTi,
        "Memory": pMe
    }
    return pInfo


if __name__ == "__main__":
    main()