#include  <QCoreApplication>
#include  <QFile>
#include  <QDomDocument>
#include  <iostream>
#include  <QDebug>
void GetConfiguration (const QDomElement *pcRootElem);
void GetCommand (const QDomElement *pcRootElem);

void Replyparameters (const QDomElement *pcRootElem);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile ocFile ("/home/rama/SampleXML/HartConfiguration.xml");
    bool bRes = ocFile.open (QIODevice::ReadOnly | QIODevice::Text);
    if (bRes == false) {

        std::cout << "Unable to open the file" << std::endl;

    }
    else {

      QDomDocument *pcXmlDoc = new QDomDocument;
      QString ocstrError = NULL;
      int ierrorLine = 0, ierrorColumn = 0;

      if (pcXmlDoc->setContent (&ocFile, true, &ocstrError,
                                &ierrorLine, &ierrorColumn) == false) {

        char szBuff[512]; szBuff[0] = '\0';
        sprintf (szBuff, "Parse error at line %d, column %d:\n%s",
                    ierrorLine, ierrorColumn, ocstrError.toStdString ().c_str ());

         std::cout << szBuff << std::endl;

      }
      else {

        QDomElement ocRootElem = pcXmlDoc->documentElement ();

          if (ocRootElem.hasChildNodes () == true)
            { GetConfiguration (&ocRootElem); }

      }
      delete pcXmlDoc; pcXmlDoc = NULL;
    }
    ocFile.close ();

    return a.exec();
}
void GetConfiguration (const QDomElement *pcRootElem)
{

  QDomElement commandSection = pcRootElem->firstChildElement ("commandSection");

  while (commandSection.isNull () == false) {
      GetCommand (&commandSection);

    commandSection = commandSection.nextSiblingElement ("commandSection");
  }

}
void GetCommand (const QDomElement *pcRootElem)
{
    QDomElement command = pcRootElem->firstChildElement ("command");

    QString ocstrName = NULL;
    while (command.isNull () == false) {

        ocstrName = command.attribute ("name");
        qDebug () << "Command Name" << ocstrName;

        QDomElement transaction = command.firstChildElement ("transaction");
         while (transaction.isNull() == false) {
             Replyparameters (&transaction);
             transaction = transaction.nextSiblingElement ("transaction");
         }

      command = command.nextSiblingElement ("command");
    }
}
void Replyparameters (const QDomElement *pcRootElem)
{

  QDomElement reply = pcRootElem->firstChildElement ("reply");

  while (reply.isNull () == false) {

      QDomElement param = reply.firstChildElement ("param");
       while (param.isNull() == false) {

           qDebug () << "name = " << param.attribute ("name");
           qDebug () << "length = " << param.attribute ("length");
           qDebug () << "type = " << param.attribute ("type");
           qDebug () << "position = "<< param.attribute ("position");

           param = param.nextSiblingElement ("param");
       }

    reply = reply.nextSiblingElement ("reply");
  }

}
