import smtplib
import time
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.base import MIMEBase
from email import encoders


def send_emails(email_to):
    for person in email_to:
        msg_send = input("write the message : ")

        if msg_send:
            body = msg_send
        else:
            body = f"""you didn't send anything"""

        msg = MIMEMultipart()
        msg['From'] = email_from
        msg['To'] = person
        msg['Subject'] = subject
        msg.attach(MIMEText(body, 'plain'))

    filename = input("attachment to be sent : ")

    if msg_send:
        print ("Great")
    else:
        filename = "../Fiddler.jpeg"        

    atta = open(filename,'rb')

    atta_pack = MIMEBase('application','octet-stream')
    atta_pack.set_payload((atta).read())
    encoders.encode_base64(atta_pack)
    atta_pack.add_header('Content-Disposition',"attachement; filename= " + filename)
    msg.attach(atta_pack)

    text = msg.as_string()
    print("connecting to server...")
    TIE_server = smtplib.SMTP(smtp_server,smtp_port)
    TIE_server.starttls()
    TIE_server.login(email_from,password)
    print("connected\n")
    TIE_server.sendmail(email_from,email_to,text)
    print(f"sending email to - {email_to}\n")
    TIE_server.quit()


smtp_port = 587
smtp_server = "smtp.gmail.com"
email_from = "flokihunterxhunter@gmail.com"
email_to = ["mohamedismailhamdani@gmail.com"]
password = "qllaaayztjocgyiq"
subject = "Webserv"

send_emails(email_to)
