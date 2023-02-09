def writeTextToFile(text):
    STATICKY_TEXT = "This is my static text which must be added to file. It is very long text and I do not know what they want to do with this terrible text. "
    FILE_NAME = "newText"
 
    newText = STATICKY_TEXT + str(text)
 
    with open(FILE_NAME, "w") as output:
        output.write(newText)
 
    return FILE_NAME