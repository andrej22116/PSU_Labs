using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;

namespace XlsxFileConverter
{
    public partial class MainWindow
    {
        private void MainWindow_DragEnter(object sender, DragEventArgs e)
        {
            if (!e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                e.Effect = DragDropEffects.None;
                return;
            }

            string[] files = e.Data.GetData(DataFormats.FileDrop) as string[];

            foreach (string file in files)
            {
                if ( Path.GetExtension(file) != ".xlsx" )
                {
                    e.Effect = DragDropEffects.None;
                    return;
                }
            }

            e.Effect = DragDropEffects.Copy | DragDropEffects.Move;
            ShowDropMessage();
        }

        private void MainWindow_DragLeave(object sender, EventArgs e)
        {
            HideDropMessage();
        }

        private void MainWindow_DragDrop(object sender, DragEventArgs e)
        {
            HideDropMessage();

            string[] files = e.Data.GetData(DataFormats.FileDrop) as string[];
            AddFilesToList(new List<string>(files));
        }

        private void ShowDropMessage()
        {
            MainPanel.Hide();
            panelDragAndDropInformation.Show();
        }

        private void HideDropMessage()
        {
            MainPanel.Show();
            panelDragAndDropInformation.Hide();
        }
    }
}
