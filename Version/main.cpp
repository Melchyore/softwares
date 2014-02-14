#include <iostream>
#include <QProcess>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDate>
#include <QTime>
#include <QFileInfo>
#include <QTemporaryFile>
#include <cstdlib>

using namespace std;

static int getBuildNumber()
{
  const QDate today(QDate::currentDate());
  return ((today.year() - 1994) * 1000) + today.dayOfYear();
}

static int getSubversionRevision()
{
  int revision = 0;
  QProcess process;
  process.start("svnversion", QStringList() << "." << "--no-newline");
  if (process.waitForStarted() && process.waitForReadyRead())
  {
    const QString str(process.readAll().constData());
    const int pos = str.indexOf(':');
    if (pos != -1)
    {
      revision = atoi(str.mid(pos + 1).toAscii().constData());
    }
    else
    {
      revision = atoi(str.toAscii().constData());
    }
    process.waitForFinished();
  }
  return revision;
}

static QByteArray readFile(const QString& fileName)
{
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly))
  {
    return QByteArray();
  }
  return file.readAll();
}

static QString version(const int major, const int minor, const int revision, const int build)
{
    QString version = QString::number(major) + "." + QString::number(minor) + "." + QString::number(revision) + "." + QString::number(build);
    return version;
}

static int writeFile(const QString& fileName, const int major, const int minor,
                        const int revision, const int build, const QString description,
                        const QString company, const QString app_name)
{
  // Create a temp file containing the version info and
  // only replace the existing one if they are different
  QTemporaryFile tempFile;
  if (tempFile.open())
  {
    QDate year = QDate::currentDate();
    QTextStream out(&tempFile);
    out << "#include <windows.h>\r\n\r\n";
    out << "VS_VERSION_INFO     VERSIONINFO\r\n";
    out << "FILEVERSION         " << major << ", " << minor << ", " << revision << ", " << build << "\r\n";
    out << "PRODUCTVERSION      " << major << ", " << minor << ", " << revision << ", " << build << "\r\n";
    out << "FILEFLAGSMASK       0x3fL\r\n";
    out << "FILEFLAGS           0\r\n";
    out << "FILETYPE            VFT_APP\r\n";
    out << "FILESUBTYPE         VFT2_UNKNOWN\r\n";
        out << "BEGIN\r\n";
        out << "    BLOCK   \"VarFileInfo\"\r\n";
        out << "    BEGIN\r\n";
        out << "        VALUE   \"Translation\",  0x409,  1200\r\n";
        out << "    END\r\n";
        out << "    BLOCK   \"StringFileInfo\"\r\n";
        out << "    BEGIN\r\n";
        out << "        BLOCK   \"040904b0\"\r\n";
        out << "        BEGIN\r\n";
        out << "            VALUE   \"CompanyName\",      \"" << company << "\"\r\n";
        out << "            VALUE   \"FileDescription\",  \"" << description <<"\"\r\n";
        out << "            VALUE   \"FileVersion\",      \"" << version(major, minor, revision, build) << "\"\r\n";
        out << "            VALUE   \"InternalName\",     \"" << app_name << "\"\r\n";
        out << "            VALUE   \"LegalCopyright\",   \"©" << year.year() << " by " << company << "\"\r\n";
        out << "            VALUE   \"OriginalFilename\", \"" << app_name << ".exe\"\r\n";
        out << "            VALUE   \"ProductName\",      \"" << app_name << "\"\r\n";
        out << "            VALUE   \"ProductVersion\",   \"" << version(major, minor, revision, build) << "\"\r\n";
        out << "        END\r\n";
        out << "    END\r\n";
        out << "END\r\n";


    const QString tempFileName = tempFile.fileName();
    tempFile.close();

    if (!QFile::exists(fileName) || readFile(fileName) != readFile(tempFileName))
    {
      QFile::remove(fileName);
      QFile::copy(tempFileName, fileName);
    }

    return 0;
  }
  else
  {
    cout << "Error creating temporary file!" << endl;
    return 1;
  }
}

int main(int argc, char *argv[])
{
  if (argc != 7)
  {
    cout << "Usage: version major minor filename" << endl;
    return 1;
  }

  const int major = atoi(argv[1]);
  const int minor = atoi(argv[2]);
  const int revision = getSubversionRevision();
  const int build = getBuildNumber();
  const QString company = argv[3];
  const QString description = argv[4];
  const QString app_name = argv[5];

  cout << major << '.' << minor << '.' << revision << '.' << build << company.toLocal8Bit().constData() << endl;

  return writeFile(argv[6], major, minor, revision, build, description, company, app_name);
}
