import smtplib
smtpObj = smtplib.SMTP('smtp.gmail.com', 587)
smtpObj.starttls()
fromm = "ipt.fb74@gmail.com"
passs = "ipt.fb74"
too = "04sabsas@gmail.com"
msg = "Awesome!  from example@gmail.com"
smtpObj.login(fromm,passs)
smtpObj.sendmail(fromm,too,msg)
smtpObj.quit()