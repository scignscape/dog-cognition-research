

void read_kv_text(QString kv_text, QMap<QString, QStringList>& result)
{
 QStringList lines = kv_text.split('\n', Qt::SkipEmptyParts);
 for(QString line : lines)
 {
  line = line.simplified();
  line.replace(": ", " ");
  QStringList tokens = line.split(' ');
  if(tokens.isEmpty())
     continue;
  result[tokens.takeFirst()] = tokens;
 }
}



