# Import smtplib for the actual sending function
import smtplib

# Import the email modules we'll need
from email.mime.text import MIMEText

# Open a plain text file for reading.  For this example, assume that
# the text file contains only ASCII characters.
subject = "This is a test"
payload = "This is a test from bank"
# Create a text/plain message
msg = MIMEText(payload)

sender = "sender"
receiver = "receiver"

SMTPServer = "SMTPServer"
# if login is needed
# username = "username with domain"
# password = "password"

# receiver = "eakasit.tangmun@gmail.com"
msg['Subject'] = 'The contents of %s' % subject
msg['From'] = sender
msg['To'] = receiver

# Send the message via our own SMTP server, but don't include the
# envelope header.
s = smtplib.SMTP(SMTPServer)
# For secure transmission
# s.starttls()

# s.login(username, password)
s.sendmail(sender, receiver, msg.as_string())
s.quit()
