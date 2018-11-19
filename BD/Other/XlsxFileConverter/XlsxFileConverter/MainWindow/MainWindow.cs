using System;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace XlsxFileConverter
{
    public partial class MainWindow : Form
    {
        public MainWindow()
        {
            InitializeComponent();
            InitializeFileListContextMenu();

            panelConvertFilesStatus.Hide();
        }

        private void buttonDoing_Click(object sender, EventArgs e)
        {
            var xlsxConverter = new XlsxTargetParser();
            xlsxConverter.TargetPath = textBox_TargetDir.Text;
            xlsxConverter.FileNameList = GetFileNameList();

            if (radioSaveMode_NewFile.Checked)
                xlsxConverter.SaveMode = XlsxTargetParser.SaveResultMode.SaveMode_ToNewFile;
            else if (radioSaveMode_NewPage.Checked)
                xlsxConverter.SaveMode = XlsxTargetParser.SaveResultMode.SaveMode_ToOldFile_NewPage;
            else if (radioSaveMode_OneFileOnePage.Checked)
                xlsxConverter.SaveMode = XlsxTargetParser.SaveResultMode.SaveMode_ToNewFile_OnePage;
            else if (radioSaveMode_OneFileManyPages.Checked)
                xlsxConverter.SaveMode = XlsxTargetParser.SaveResultMode.SaveMode_ToNewFile_ManyPages;

            MainPanel.Hide();
            panelConvertFilesStatus.Show();
            buttonConvertProcessOk.Hide();

            xlsxConverter.OnProcess_Info += (TaskStatus status, string message) => {
                if (status == TaskStatus.Faulted)
                {
                    MessageBox.Show(this, message, "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                labelConvertProcessStatus.Text = message;
                labelConvertProcessStatus.Refresh();

                if (status == TaskStatus.RanToCompletion)
                {
                    buttonConvertProcessOk.Show();
                }
            };

            xlsxConverter.runConvert();
        }

        private void buttonConvertProcessOk_Click(object sender, EventArgs e)
        {
            MainPanel.Show();
            panelConvertFilesStatus.Hide();
        }

        private void buttonAddFiles_Click(object sender, EventArgs e)
        {
            GetFilesWithFileloadDialog();
        }

        private void OnSetCheckToSaveNewFileMode(object sender, EventArgs e)
        {
            tableLayout_TargetDir.Enabled = true; ;
        }

        private void OnSetCheckToSaveOldFileMode(object sender, EventArgs e)
        {
            tableLayout_TargetDir.Enabled = false;
        }

        private void textBox_TargetDir_Leave(object sender, EventArgs e)
        {
            if (textBox_TargetDir.Text.Length == 0)
            {
                textBox_TargetDir.Text = ".\\";
            }
            else if (textBox_TargetDir.Text.Last() != '\\')
            {
                textBox_TargetDir.Text += '\\';
            }
        }

        private void GetFilesWithFileloadDialog()
        {
            var dialog = new OpenFileDialog();
            dialog.CheckFileExists = true;
            dialog.AddExtension = true;
            dialog.Filter = "Excel 2007 and more (*.xlsx)|*.xlsx";
            dialog.InitialDirectory = textBox_TargetDir.Text;
            dialog.Multiselect = true;
            dialog.Title = "Выбрать файлы для конвертации";
            dialog.FilterIndex = 0;

            dialog.ShowDialog(this);

            AddFilesToList(dialog.FileNames);
        }

        private void buttonSetSaveResultCurrentDir_Click(object sender, EventArgs e)
        {
            var dialog = new FolderBrowserDialog();
            dialog.ShowNewFolderButton = true;
            dialog.ShowDialog();

            textBox_TargetDir.Text = dialog.SelectedPath + "\\";
        }
    }
}
