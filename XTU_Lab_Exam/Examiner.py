from selenium import webdriver
import time
import AnswerModel


def login(uid, password, code):
    login_account = driver.find_element_by_name('login1$txtName')
    login_account.clear()
    login_account.send_keys(uid)

    login_password = driver.find_element_by_name('login1$txtPwd')
    login_password.clear()
    login_password.send_keys(password)

    login_code = driver.find_element_by_name('login1$txt_Code')
    login_code.clear()
    login_code.send_keys(code)

    login_code = driver.find_element_by_name('login1$Btn_Login')
    login_code.click()


def logout():
    logout_index = driver.find_element_by_id("i_1")
    logout_index.click()

    time.sleep(0.5)

    logout_button = driver.find_element_by_css_selector("#login1_LinkButton1 > b")
    logout_button.click()


def selectExam(exam_type, exam_id):
    exam_start = driver.find_element_by_id("i_5")
    exam_start.click()
    time.sleep(2)
    if exam_type == "test":
        if int(exam_id) == 1:
            exam_practice_1 = driver.find_element_by_css_selector("tr:nth-child(2) a:nth-child(2)")
            exam_practice_1.click()
            print("选择 测试题 1")
        else:
            exam_practice_2 = driver.find_element_by_css_selector("tr:nth-child(3) a:nth-child(2)")
            exam_practice_2.click()
            print("选择 测试题 2")
    else:
        if int(exam_id) == 1:
            exam_1 = driver.find_element_by_id("ctl00_ContentPlaceHolder1_GridView1_ctl02_lnkenter")
            exam_1.click()
            print("选择 考试题 1")
        else:
            exam_2 = driver.find_element_by_id("ctl00_ContentPlaceHolder1_GridView1_ctl03_lnkenter")
            exam_2.click()
            print("选择 考试题 2")

        time.sleep(1)
        alert = driver.switch_to_alert()
        time.sleep(0.5)
        alert.accept()
        print("确认参加考试")


def doTestExam():
    elements = driver.find_elements_by_tag_name("b")
    problemName = elements[0]
    problemName = problemName.text[problemName.text.find("、") + 1:]
    choices = elements[1:]
    print(problemName)
    try:
        problemAnswerIndex = answersProblemName.index(problemName)
    except:
        print("Error: can't index!")
        return
    problemAnswer = answers[problemAnswerIndex][1]
    print("answer:" + problemAnswer)

    inputs = driver.find_elements_by_tag_name("input")
    radios = []
    for input_item in inputs:
        if input_item.get_attribute("type") == "radio" or input_item.get_attribute("type") == "checkbox":
            radios.append(input_item)
    choose_list = []
    for iid, choice in enumerate(choices):
        print(choice.text, problemAnswer)
        if choice.text == problemAnswer:  # 单选题
            choose_list.append(iid)
            print("Add Click:" + str(iid))
        if problemAnswer.find(choice.text[:choice.text.find("、")]) != -1:  # 单选题&多选题
            choose_list.append(iid)
            print("Add Click:" + str(iid))

    for need_choose in choose_list:
        radios[need_choose].click()
        print("Do Click:" + str(need_choose))
        time.sleep(0.1)
    buttonOK = driver.find_element_by_name("ctl00$ContentPlaceHolder1$btnOk")
    buttonOK.click()
    time.sleep(0.2)
    buttonNext = driver.find_element_by_name("ctl00$ContentPlaceHolder1$btnNext")
    buttonNext.click()


def doExam():
    answer_question = driver.find_elements_by_id("Table2")
    for question in answer_question:
        problemName = question.find_element_by_tag_name("span")
        problemName = problemName.text[problemName.text.find("、") + 1:]
        print(problemName)
        try:
            problemAnswerIndex = answersProblemName.index(problemName)
        except:
            print("Error: can't index!")
            continue
        problemAnswer = answers[problemAnswerIndex][1]
        print("answer:" + problemAnswer)

        inputs = question.find_elements_by_tag_name("input")
        labels = question.find_elements_by_tag_name("label")
        choose_list = []
        for iid, answer_choice in enumerate(labels):
            print(answer_choice.text)
            if problemAnswer.find(answer_choice.text[answer_choice.text.find("、") + 1:]) != -1:  # 判断题
                choose_list.append(iid)
                print("Add Clicks:" + str(iid))
            if problemAnswer.find(answer_choice.text[:answer_choice.text.find("、")]) != -1:  # 单选题&多选题
                choose_list.append(iid)
                print("Add Clicks:" + str(iid))
        for need_choose in choose_list:
            try:
                inputs[need_choose].click()
                if not inputs[need_choose].is_selected():
                    print("Error: Can't click! Please click #" + str(need_choose) + "# by hand and press enter to go on")
                    input()
                    continue
                print("Do Click:" + str(need_choose))
                time.sleep(0.1)
            except:
                print("Error: Can't click! Please click #" + str(need_choose) + "# by hand and press enter to go on")
                input()

        time.sleep(1)
        buttonOK = driver.find_element_by_name("btnjj")
        buttonOK.click()


if __name__ == "__main__":
    print("启动半自动模式(专业模式)请输入 pro , 输入其他进入全自动模式")
    mode = input()
    if mode == "pro":
        # 打印使用方法
        print("软件专业模式使用方法:")
        print("init default 默认初始化")
        print("init answer [题库文件路径] 初始化题库文件")
        print("init selenium 初始化selenium")
        print("login [学号] [验证码] 自动填写账号密码验证码")
        print("test [做题数] 做测试题")
        print("exam 做考试题")
        print("title 查看当前窗口标题")
        print("window 查看所有窗口")
        print("switch [窗口ID] 切换至指定窗口(ID指第几个窗口，从1开始)")
        print("select [test/exam] [考试ID] 选择指定的考试题或者测试题")
        print("quit 退出")

        while True:
            command_raw = input()
            command = command_raw.split(" ")
            # Command start
            if command[0] == "init":
                if command[1] == "default":
                    driver = webdriver.Chrome()
                    answers = AnswerModel.AnswerCSVToList("answerlist.csv")
                    answersProblemName = []
                    driver.get("http://sys.xtu.edu.cn/aqzr/")
                    for index, answer in enumerate(answers):
                        answers[index][0] = answer[0][answer[0].find("、") + 1:]
                        answersProblemName.append(answers[index][0])
                if command[1] == "answer":
                    answers = AnswerModel.AnswerCSVToList(command[2])
                    answersProblemName = []
                    for index, answer in enumerate(answers):
                        answers[index][0] = answer[0][answer[0].find("、") + 1:]
                        answersProblemName.append(answers[index][0])
                if command[1] == "selenium":
                    driver = webdriver.Chrome()
                    driver.get("http://sys.xtu.edu.cn/aqzr/")
            if command[0] == "test":
                try:
                    for i in range(int(command[1])):
                        doTestExam()
                        time.sleep(0.2)
                    print("做测试题 完毕")
                except:
                    print("命令输入错误: test [做题数] 或 未切换至对应窗口")
            if command[0] == "exam":
                doExam()
                print("做考试题 完毕")
            if command[0] == "login":
                login(command[1], command[1], command[2])
                print("登录成功")
            if command[0] == "window":
                print(driver.window_handles)
            if command[0] == "title":
                print(driver.title)
            if command[0] == "switch":
                try:
                    driver.switch_to.window(driver.window_handles[int(command[1]) - 1])
                    print("切换到:" + str(driver.window_handles[int(command[1]) - 1]))
                except:
                    print("切换失败")
            if command[0] == "select":
                try:
                    selectExam(command[1], command[2])
                except:
                    print("失败")
            if command[0] == "quit":
                quit()
            if command[0] == "logout":
                logout()
    else:  # 自动模式
        driver = webdriver.Chrome()
        driver.get("http://sys.xtu.edu.cn/aqzr/")

        print("请输入你的学号:")
        xh = input()
        print("请输入你的密码(与学号相同请直接回车):")
        mm = input()
        if mm == "":
            mm = xh
        print("请输入页面上的验证码:")
        yzm = input()

        answers = AnswerModel.AnswerCSVToList("answerlist.csv")
        answersProblemName = []
        for index, answer in enumerate(answers):
            answers[index][0] = answer[0][answer[0].find("、") + 1:]
            answersProblemName.append(answers[index][0])

        login(xh, mm, yzm)
        print("自动模式 - 登录")
        time.sleep(0.5)

        for x in range(1, 3):
            selectExam("test", x)
            print("自动模式 - 进入考试" + str(x) + "测试题界面")
            time.sleep(1.5)
            for i in range(100):
                doTestExam()
                time.sleep(0.2)
            print("自动模式 - 考试" + str(x) + "测试题完成100道")
            alert = driver.switch_to_alert()
            time.sleep(0.5)
            alert.accept()

            selectExam("test", x)
            print("自动模式 - 再次进入考试" + str(x) + "测试题界面")
            time.sleep(1.5)
            for i in range(100):
                doTestExam()
                time.sleep(0.2)
            print("自动模式 - 考试" + str(x) + "测试题完成200道")
            alert = driver.switch_to_alert()
            time.sleep(0.5)
            alert.accept()

            selectExam("exam", x)
            print("自动模式 - 开始尝试切换到考试" + str(x) + "窗口")
            for handle in driver.window_handles:
                try:
                    driver.switch_to.window(handle)
                    print("切换到:" + handle)
                    print("尝试开始考试" + str(x))
                    try:
                        doExam()
                        print("考试" + str(x) + "完成")
                    except:
                        print("开始考试" + str(x) + "失败")
                except:
                    print("切换失败:" + handle)
        print("执行完毕!")

