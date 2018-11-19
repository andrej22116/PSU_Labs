using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace XlsxFileConverter
{
    public partial class MainWindow
    {
        private ContextMenuStrip contextMenu_FileList = new ContextMenuStrip();

        private void InitializeFileListContextMenu()
        {
            var menuItems = new ToolStripItem[]
            {
                new ToolStripMenuItem { Text = "Добавить файлы" },
                new ToolStripMenuItem { Text = "Удалить выделеное" }
            };

            menuItems[0].MouseDown += OnAddFilesMenuItem_Click;
            menuItems[1].MouseDown += OnRemoveFilesMenuItem_Click;

            contextMenu_FileList.Items.AddRange(menuItems);
            fileList.MouseDown += OnFileList_MouseClick;
            fileList.KeyDown += OnFileList_KeyboardKeyPressed;
        }

        #region Обработка важных событий.

        private void OnAddFilesMenuItem_Click(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Left)
            {
                return;
            }

            contextMenu_FileList.Visible = false;

            GetFilesWithFileloadDialog();
        }

        private void OnRemoveFilesMenuItem_Click(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Left)
            {
                return;
            }

            contextMenu_FileList.Visible = false;

            RemoveSelectedFilesFromList();
        }

        private void OnFileList_MouseClick(object sender, MouseEventArgs e)
        {
            if ( e.Button != MouseButtons.Right )
            {
                contextMenu_FileList.Visible = false;
                return;
            }

            contextMenu_FileList.Show(Cursor.Position);
            contextMenu_FileList.Visible = true;
        }

        private void OnFileList_KeyboardKeyPressed(object sender, KeyEventArgs e)
        {
            if ( e.KeyCode == Keys.Delete )
            {
                RemoveSelectedFilesFromList();
            }
        }

        #endregion

        #region Логика работы с списком файлов

        private void AddFilesToList(IEnumerable<string> fileNameList)
        {
            foreach ( string fileName in fileNameList )
            {
                if ( !fileList.Items.Contains(fileName) )
                {
                    fileList.Items.Add(fileName);
                }
            }
        }

        private void RemoveSelectedFilesFromList()
        {
            while ( fileList.SelectedIndex != -1 )
            {
                fileList.Items.Remove(fileList.Items[fileList.SelectedIndex]);
            }
        }

        private IEnumerable<string> GetFileNameList()
        {
            return fileList.Items.Cast<string>();
        }

        #endregion
    }
}
