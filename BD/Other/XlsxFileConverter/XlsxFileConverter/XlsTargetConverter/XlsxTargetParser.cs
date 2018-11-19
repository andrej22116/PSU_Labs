using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

using OfficeOpenXml;

namespace XlsxFileConverter
{
    using StringList = IEnumerable<string>;

    public partial class XlsxTargetParser
    {
        #region Константы
        private const string messageTemplateStartConvertFile =
            "Конвертация файла: \"{0}\" - начато!";

        private const string messageTemplateCompleteConvertFile =
            "Конвертация файла: \"{0}\" - завершено!";

        private const string messageTemplateErrorOnConvertFile =
            "Возникла ошибка во время конвертации файла: \"{0}\", ошибка: \"{1}\".";

        private static Regex lineSplitRegex = new Regex("[^\\d\\\\:\\.]+");
        #endregion

        #region Поля класса и их типы, используемые при конвертации файлов.


        public enum SaveResultMode
        {
            /**------------------------------------------------------------------
             * SaveMode_ToOldFile_NewPage - Добавление в каждый файл новой 
             * страницы с результатом.
             * ------------------------------------------------------------------
             * SaveMode_ToNewFile - Результат обработки каждого файла будет 
             * записан в новый файл
             * ------------------------------------------------------------------
             * SaveMode_ToNewFile_OnePage - Результат обработки каждого файла 
             * будет сохранён в один файл на одной странице
             * ------------------------------------------------------------------
             * SaveMode_ToNewFile_ManyPages - Результат обработки каждого файла 
             * будет сохранён в один файл, но для каждого результата будет
             * создана отдельная страница
             * ------------------------------------------------------------------
             */

            SaveMode_ToOldFile_NewPage,
            SaveMode_ToNewFile,
            SaveMode_ToNewFile_OnePage,
            SaveMode_ToNewFile_ManyPages
        }

        private StringList _fileNameList;
        public StringList FileNameList
        {
            get { return _fileNameList; }
            set
            {
                if ( value == null )
                {
                    throw new ArgumentException();
                }
                _fileNameList = value;
            }
        }

        public SaveResultMode SaveMode { get; set; }

        public string _targetPath;
        public string TargetPath
        {
            get { return _targetPath; }
            set
            {
                _targetPath = value ?? throw new ArgumentException();
                if ( !Directory.Exists(value) )
                {
                    throw new ArgumentException();
                }
            }
        }


        //private Dictionary<IEnumerable<string[]>> 

        #endregion

        #region Делегаты и их объекты

        public delegate void XlsxParsInfoCallbackDelegate(TaskStatus status, string message);
        public XlsxParsInfoCallbackDelegate OnProcess_Info;

        private delegate void XlsxSaveMethodDelegate(string fileName, IEnumerable<string[]> parsedData);
        private XlsxSaveMethodDelegate SaveMethod;

        #endregion

        public XlsxTargetParser ()
        {
            SaveMode = SaveResultMode.SaveMode_ToNewFile;
        }

        public XlsxTargetParser(StringList fileNameList,
            string targetPath, SaveResultMode saveMode)
        {
            _fileNameList = fileNameList;
            _targetPath = targetPath;
            SaveMode = saveMode;
        }


        public void runConvert()
        {
            try
            {
                OnProcess_Info?.Invoke(TaskStatus.Running, "Проверка исходных данных...");
                if ( !Directory.Exists(_targetPath) )
                {
                    throw new Exception(string.Format("Целевой каталог \"{0}\" не существует!", TargetPath));
                }
                if ( _fileNameList == null || _fileNameList.Count() == 0 )
                {
                    throw new Exception("Список обрабатываемых файлов пуст!");
                }

                switch (SaveMode)
                {
                    case SaveResultMode.SaveMode_ToNewFile:
                        { SaveToNewFile(); } break;

                    case SaveResultMode.SaveMode_ToOldFile_NewPage:
                        { SaveToOldFileInNewPage(); } break;

                    case SaveResultMode.SaveMode_ToNewFile_OnePage:
                        { SaveToOneFileOnePage(); }  break;

                    case SaveResultMode.SaveMode_ToNewFile_ManyPages:
                        { SaveToOneFileManyPages(); } break;
                }

                OnProcess_Info?.Invoke(TaskStatus.RanToCompletion, "Готово!");
            }
            catch (Exception ex)
            {
                OnProcess_Info?.Invoke(TaskStatus.Faulted, "Ошибка! => " + ex.ToString());
                OnProcess_Info?.Invoke(TaskStatus.RanToCompletion, "Ошибка! => " + ex.ToString());
            }
        }
    }
}
