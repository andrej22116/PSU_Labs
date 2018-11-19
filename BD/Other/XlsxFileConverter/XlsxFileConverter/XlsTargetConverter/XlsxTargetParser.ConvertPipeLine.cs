using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

using OfficeOpenXml;

namespace XlsxFileConverter
{
    using StringList = IEnumerable<string>;

    public partial class XlsxTargetParser
    {
        #region Парсинг входных данных

        private IEnumerable<StringList> parse(ExcelWorksheet excelWorksheet)
        {
            var allLinesFromWorksheet = getAllLinesFromWorksheet(excelWorksheet);
            return parseAllLines(allLinesFromWorksheet);
        }

        private StringList getAllLinesFromWorksheet(ExcelWorksheet excelWorksheet)
        {
            var lineList = new List<string>();

            int i = 1;
            while (excelWorksheet.Cells[i, 1].Text.Length != 0)
            {
                lineList.Add(excelWorksheet.Cells[i++, 1].Text);
            }

            return lineList;
        }

        private IEnumerable<StringList> parseAllLines(StringList lineList)
        {
            var parsedDataList = new List<StringList>();

            foreach (string line in lineList)
            {
                parsedDataList.Add(parseLine(line));
            }

            return parsedDataList;
        }

        private StringList parseLine(string line)
        {
            return lineSplitRegex.Split(line);
        }

        private void WriteParsedDataToWorksheetRow(ExcelWorksheet package, int row, StringList data)
        {
            package.Cells[row, 1].Value = int.Parse(data.ElementAt(0));
            package.Cells[row, 2].Value = int.Parse(data.ElementAt(1));
            package.Cells[row, 3].Value = int.Parse(data.ElementAt(2));
            package.Cells[row, 4].Value = int.Parse(data.ElementAt(3));
            package.Cells[row, 5].Value = double.Parse(data.ElementAt(4).Replace('.', ','));
            package.Cells[row, 6].Value = data.ElementAt(5);
        }

        #endregion

        #region Методы сохранения результата работы конвертатора

        private delegate ExcelPackage XlsxConverteProcessOpenFile(string fileName);
        private delegate void XlsxConverteProcessWriteParseResult(IEnumerable<StringList> parseResult);
        private delegate void XlsxConverteProcessSaveResult();

        private void parse( XlsxConverteProcessOpenFile onOpenFile
                          , XlsxConverteProcessWriteParseResult onParseContinue
                          , XlsxConverteProcessSaveResult onCloseFile )
        {
            foreach (string fileName in _fileNameList)
            {
                OnProcess_Info?.Invoke(TaskStatus.Running,
                    string.Format(messageTemplateStartConvertFile, fileName));

                try
                {
                    using (var excelDocument = onOpenFile?.Invoke(fileName))
                    {
                        var firstDocumentWorksheet = excelDocument.Workbook.Worksheets.First();
                        var parsedDataList = parse(firstDocumentWorksheet);

                        onParseContinue?.Invoke(parsedDataList);

                        onCloseFile?.Invoke();
                    }
                }
                catch (Exception ex)
                {
                    OnProcess_Info?.Invoke(TaskStatus.Faulted,
                        string.Format(messageTemplateErrorOnConvertFile,
                            fileName, ex.ToString()));
                    continue;
                }

                OnProcess_Info?.Invoke(TaskStatus.Running,
                    string.Format(messageTemplateCompleteConvertFile, fileName));
            }
        }

        private void SaveToOneFileManyPages()
        {
            using (var resultDocument = new ExcelPackage())
            {
                int i = 1;
                string curentFileName = "";

                string newFileName = string.Format("{0}\\Xlsx_ConvertResult.xlsx",
                    _targetPath);

                parse(
                    filename => {
                        curentFileName = filename;
                        return new ExcelPackage(new FileInfo(filename));
                    }, 
                    parseResult => {
                         var newDocumentWorksheet = resultDocument.Workbook.Worksheets.Add(
                             string.Format("Результат_{0}_{1}", i++, curentFileName));

                        int row = 1;
                        foreach (var data in parseResult)
                        {
                            WriteParsedDataToWorksheetRow(newDocumentWorksheet, row++, data);
                        }
                    }
                    , () => {
                        resultDocument.SaveAs(new FileInfo(newFileName));
                    }
                );
            }
        }

        private void SaveToOneFileOnePage()
        {
            using (var resultDocument = new ExcelPackage())
            {
                int row = 1;
                string curentFileName = "";

                string newFileName = string.Format("{0}\\Xlsx_ConvertResult.xlsx",
                    _targetPath);

                var newDocumentWorksheet = resultDocument.Workbook.Worksheets.Add("Результат");

                parse(
                    filename => {
                        curentFileName = filename;
                        return new ExcelPackage(new FileInfo(filename));
                    },
                    parseResult => {
                        foreach (var data in parseResult)
                        {
                            WriteParsedDataToWorksheetRow(newDocumentWorksheet, row++, data);
                        }
                    }
                    , () => {
                        resultDocument.SaveAs(new FileInfo(newFileName));
                    }
                );
            }
        }

        private void SaveToOldFileInNewPage()
        {
            ExcelPackage currentDocument = null;

            parse(
                filename => {
                    currentDocument = new ExcelPackage(new FileInfo(filename));
                    return currentDocument;
                },
                parseResult => {
                    var newDocumentWorksheet = currentDocument.Workbook.Worksheets["Результат"];
                    if (newDocumentWorksheet == null)
                    {
                        newDocumentWorksheet = currentDocument.Workbook.Worksheets.Add("Результат");
                    }

                    int row = 1;
                    foreach (var data in parseResult)
                    {
                        WriteParsedDataToWorksheetRow(newDocumentWorksheet, row++, data);
                    }
                }
                , () => {
                    currentDocument.Save();
                    currentDocument.Dispose();
                }
            );
        }

        private void SaveToNewFile()
        {
            string newFileName = "";

            parse(
                filename => {
                    newFileName = string.Format("{0}\\{1}_ConvertResult.xlsx",
                        _targetPath, Path.GetFileNameWithoutExtension(filename));
                    return new ExcelPackage(new FileInfo(filename));
                },
                parseResult => {
                    using (var resultDocument = new ExcelPackage())
                    {
                        var newDocumentWorksheet = resultDocument.Workbook.Worksheets.Add("Результат");

                        int row = 1;
                        foreach (var data in parseResult)
                        {
                            WriteParsedDataToWorksheetRow(newDocumentWorksheet, row++, data);
                        }

                        resultDocument.SaveAs(new FileInfo(newFileName));
                    }
                }
                , null
            );
        }
    }

    #endregion
}
