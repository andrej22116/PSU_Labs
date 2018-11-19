namespace XlsxFileConverter
{
    partial class MainWindow
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.fileList = new System.Windows.Forms.ListBox();
            this.buttonDoing = new System.Windows.Forms.Button();
            this.buttonAddFiles = new System.Windows.Forms.Button();
            this.radioSaveMode_NewFile = new System.Windows.Forms.RadioButton();
            this.radioSaveMode_NewPage = new System.Windows.Forms.RadioButton();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.tableLayout_TargetDir = new System.Windows.Forms.TableLayoutPanel();
            this.label2 = new System.Windows.Forms.Label();
            this.buttonSetSaveResultCurrentDir = new System.Windows.Forms.Button();
            this.textBox_TargetDir = new System.Windows.Forms.TextBox();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.radioSaveMode_OneFileManyPages = new System.Windows.Forms.RadioButton();
            this.radioSaveMode_OneFileOnePage = new System.Windows.Forms.RadioButton();
            this.MainPanel = new System.Windows.Forms.Panel();
            this.panelConvertFilesStatus = new System.Windows.Forms.Panel();
            this.buttonConvertProcessOk = new System.Windows.Forms.Button();
            this.labelConvertProcessStatus = new System.Windows.Forms.Label();
            this.panelDragAndDropInformation = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.InfoLabel_1 = new System.Windows.Forms.Label();
            this.InfoLabel_2 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.tableLayout_TargetDir.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.MainPanel.SuspendLayout();
            this.panelConvertFilesStatus.SuspendLayout();
            this.panelDragAndDropInformation.SuspendLayout();
            this.panel3.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox1.Controls.Add(this.tableLayoutPanel1);
            this.groupBox1.Location = new System.Drawing.Point(4, 195);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox1.Size = new System.Drawing.Size(576, 230);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "[ Файлы ]";
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 17.41007F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 277F));
            this.tableLayoutPanel1.Controls.Add(this.fileList, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.buttonDoing, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.buttonAddFiles, 1, 1);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(4, 19);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 73.85321F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.Size = new System.Drawing.Size(568, 207);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // fileList
            // 
            this.tableLayoutPanel1.SetColumnSpan(this.fileList, 2);
            this.fileList.Dock = System.Windows.Forms.DockStyle.Fill;
            this.fileList.FormattingEnabled = true;
            this.fileList.ItemHeight = 16;
            this.fileList.Location = new System.Drawing.Point(3, 3);
            this.fileList.Name = "fileList";
            this.fileList.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended;
            this.fileList.Size = new System.Drawing.Size(562, 149);
            this.fileList.Sorted = true;
            this.fileList.TabIndex = 0;
            // 
            // buttonDoing
            // 
            this.buttonDoing.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.buttonDoing.Location = new System.Drawing.Point(3, 158);
            this.buttonDoing.Name = "buttonDoing";
            this.buttonDoing.Size = new System.Drawing.Size(200, 46);
            this.buttonDoing.TabIndex = 1;
            this.buttonDoing.Text = "Обработать";
            this.buttonDoing.UseVisualStyleBackColor = true;
            this.buttonDoing.Click += new System.EventHandler(this.buttonDoing_Click);
            // 
            // buttonAddFiles
            // 
            this.buttonAddFiles.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonAddFiles.Location = new System.Drawing.Point(365, 158);
            this.buttonAddFiles.Name = "buttonAddFiles";
            this.buttonAddFiles.Size = new System.Drawing.Size(200, 46);
            this.buttonAddFiles.TabIndex = 2;
            this.buttonAddFiles.Text = "Добавить файлы";
            this.buttonAddFiles.UseVisualStyleBackColor = true;
            this.buttonAddFiles.Click += new System.EventHandler(this.buttonAddFiles_Click);
            // 
            // radioSaveMode_NewFile
            // 
            this.radioSaveMode_NewFile.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.radioSaveMode_NewFile.AutoSize = true;
            this.radioSaveMode_NewFile.Checked = true;
            this.radioSaveMode_NewFile.Location = new System.Drawing.Point(4, 4);
            this.radioSaveMode_NewFile.Margin = new System.Windows.Forms.Padding(4);
            this.radioSaveMode_NewFile.Name = "radioSaveMode_NewFile";
            this.radioSaveMode_NewFile.Size = new System.Drawing.Size(126, 24);
            this.radioSaveMode_NewFile.TabIndex = 0;
            this.radioSaveMode_NewFile.TabStop = true;
            this.radioSaveMode_NewFile.Text = "... новые файлы";
            this.radioSaveMode_NewFile.UseVisualStyleBackColor = true;
            this.radioSaveMode_NewFile.CheckedChanged += new System.EventHandler(this.OnSetCheckToSaveNewFileMode);
            // 
            // radioSaveMode_NewPage
            // 
            this.radioSaveMode_NewPage.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.radioSaveMode_NewPage.AutoSize = true;
            this.radioSaveMode_NewPage.Location = new System.Drawing.Point(4, 36);
            this.radioSaveMode_NewPage.Margin = new System.Windows.Forms.Padding(4);
            this.radioSaveMode_NewPage.Name = "radioSaveMode_NewPage";
            this.radioSaveMode_NewPage.Size = new System.Drawing.Size(237, 24);
            this.radioSaveMode_NewPage.TabIndex = 1;
            this.radioSaveMode_NewPage.Text = "... старый файл - новая страница";
            this.radioSaveMode_NewPage.UseVisualStyleBackColor = true;
            this.radioSaveMode_NewPage.CheckedChanged += new System.EventHandler(this.OnSetCheckToSaveOldFileMode);
            // 
            // groupBox3
            // 
            this.groupBox3.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox3.Controls.Add(this.tableLayout_TargetDir);
            this.groupBox3.Controls.Add(this.tableLayoutPanel2);
            this.groupBox3.Location = new System.Drawing.Point(4, 4);
            this.groupBox3.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox3.Size = new System.Drawing.Size(576, 191);
            this.groupBox3.TabIndex = 2;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Сохранение в...";
            // 
            // tableLayout_TargetDir
            // 
            this.tableLayout_TargetDir.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tableLayout_TargetDir.ColumnCount = 3;
            this.tableLayout_TargetDir.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 250F));
            this.tableLayout_TargetDir.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayout_TargetDir.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 80F));
            this.tableLayout_TargetDir.Controls.Add(this.label2, 0, 0);
            this.tableLayout_TargetDir.Controls.Add(this.buttonSetSaveResultCurrentDir, 2, 0);
            this.tableLayout_TargetDir.Controls.Add(this.textBox_TargetDir, 1, 0);
            this.tableLayout_TargetDir.Location = new System.Drawing.Point(0, 22);
            this.tableLayout_TargetDir.Name = "tableLayout_TargetDir";
            this.tableLayout_TargetDir.RowCount = 1;
            this.tableLayout_TargetDir.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayout_TargetDir.Size = new System.Drawing.Size(576, 34);
            this.tableLayout_TargetDir.TabIndex = 8;
            // 
            // label2
            // 
            this.label2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(0, 9);
            this.label2.Margin = new System.Windows.Forms.Padding(0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(250, 16);
            this.label2.TabIndex = 5;
            this.label2.Text = "Каталог для сохранения результата:";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // buttonSetSaveResultCurrentDir
            // 
            this.buttonSetSaveResultCurrentDir.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonSetSaveResultCurrentDir.Location = new System.Drawing.Point(499, 5);
            this.buttonSetSaveResultCurrentDir.Name = "buttonSetSaveResultCurrentDir";
            this.buttonSetSaveResultCurrentDir.Size = new System.Drawing.Size(74, 23);
            this.buttonSetSaveResultCurrentDir.TabIndex = 6;
            this.buttonSetSaveResultCurrentDir.Text = "Выбрать";
            this.buttonSetSaveResultCurrentDir.UseVisualStyleBackColor = true;
            this.buttonSetSaveResultCurrentDir.Click += new System.EventHandler(this.buttonSetSaveResultCurrentDir_Click);
            // 
            // textBox_TargetDir
            // 
            this.textBox_TargetDir.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.textBox_TargetDir.Location = new System.Drawing.Point(253, 6);
            this.textBox_TargetDir.Name = "textBox_TargetDir";
            this.textBox_TargetDir.Size = new System.Drawing.Size(240, 22);
            this.textBox_TargetDir.TabIndex = 7;
            this.textBox_TargetDir.Text = ".\\";
            this.textBox_TargetDir.Leave += new System.EventHandler(this.textBox_TargetDir_Leave);
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tableLayoutPanel2.ColumnCount = 1;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.Controls.Add(this.radioSaveMode_OneFileManyPages, 0, 3);
            this.tableLayoutPanel2.Controls.Add(this.radioSaveMode_NewFile, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.radioSaveMode_NewPage, 0, 1);
            this.tableLayoutPanel2.Controls.Add(this.radioSaveMode_OneFileOnePage, 0, 2);
            this.tableLayoutPanel2.Location = new System.Drawing.Point(0, 56);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 4;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(576, 131);
            this.tableLayoutPanel2.TabIndex = 3;
            // 
            // radioSaveMode_OneFileManyPages
            // 
            this.radioSaveMode_OneFileManyPages.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.radioSaveMode_OneFileManyPages.AutoSize = true;
            this.radioSaveMode_OneFileManyPages.Location = new System.Drawing.Point(4, 100);
            this.radioSaveMode_OneFileManyPages.Margin = new System.Windows.Forms.Padding(4);
            this.radioSaveMode_OneFileManyPages.Name = "radioSaveMode_OneFileManyPages";
            this.radioSaveMode_OneFileManyPages.Size = new System.Drawing.Size(258, 27);
            this.radioSaveMode_OneFileManyPages.TabIndex = 3;
            this.radioSaveMode_OneFileManyPages.Text = "... один новый файл - много страниц";
            this.radioSaveMode_OneFileManyPages.UseVisualStyleBackColor = true;
            this.radioSaveMode_OneFileManyPages.CheckedChanged += new System.EventHandler(this.OnSetCheckToSaveNewFileMode);
            // 
            // radioSaveMode_OneFileOnePage
            // 
            this.radioSaveMode_OneFileOnePage.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.radioSaveMode_OneFileOnePage.AutoSize = true;
            this.radioSaveMode_OneFileOnePage.Location = new System.Drawing.Point(4, 68);
            this.radioSaveMode_OneFileOnePage.Margin = new System.Windows.Forms.Padding(4);
            this.radioSaveMode_OneFileOnePage.Name = "radioSaveMode_OneFileOnePage";
            this.radioSaveMode_OneFileOnePage.Size = new System.Drawing.Size(259, 24);
            this.radioSaveMode_OneFileOnePage.TabIndex = 2;
            this.radioSaveMode_OneFileOnePage.Text = "... один новый файл - одна страница";
            this.radioSaveMode_OneFileOnePage.UseVisualStyleBackColor = true;
            this.radioSaveMode_OneFileOnePage.CheckedChanged += new System.EventHandler(this.OnSetCheckToSaveNewFileMode);
            // 
            // MainPanel
            // 
            this.MainPanel.Controls.Add(this.groupBox1);
            this.MainPanel.Controls.Add(this.groupBox3);
            this.MainPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.MainPanel.Location = new System.Drawing.Point(0, 0);
            this.MainPanel.Name = "MainPanel";
            this.MainPanel.Size = new System.Drawing.Size(584, 429);
            this.MainPanel.TabIndex = 3;
            // 
            // panelConvertFilesStatus
            // 
            this.panelConvertFilesStatus.BackColor = System.Drawing.Color.Transparent;
            this.panelConvertFilesStatus.Controls.Add(this.buttonConvertProcessOk);
            this.panelConvertFilesStatus.Controls.Add(this.labelConvertProcessStatus);
            this.panelConvertFilesStatus.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panelConvertFilesStatus.Location = new System.Drawing.Point(0, 0);
            this.panelConvertFilesStatus.Name = "panelConvertFilesStatus";
            this.panelConvertFilesStatus.Size = new System.Drawing.Size(584, 429);
            this.panelConvertFilesStatus.TabIndex = 5;
            // 
            // buttonConvertProcessOk
            // 
            this.buttonConvertProcessOk.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.buttonConvertProcessOk.Location = new System.Drawing.Point(232, 385);
            this.buttonConvertProcessOk.Name = "buttonConvertProcessOk";
            this.buttonConvertProcessOk.Size = new System.Drawing.Size(113, 32);
            this.buttonConvertProcessOk.TabIndex = 1;
            this.buttonConvertProcessOk.Text = "Продолжить";
            this.buttonConvertProcessOk.UseVisualStyleBackColor = true;
            this.buttonConvertProcessOk.Click += new System.EventHandler(this.buttonConvertProcessOk_Click);
            // 
            // labelConvertProcessStatus
            // 
            this.labelConvertProcessStatus.BackColor = System.Drawing.Color.Transparent;
            this.labelConvertProcessStatus.Dock = System.Windows.Forms.DockStyle.Fill;
            this.labelConvertProcessStatus.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelConvertProcessStatus.Location = new System.Drawing.Point(0, 0);
            this.labelConvertProcessStatus.Margin = new System.Windows.Forms.Padding(10);
            this.labelConvertProcessStatus.Name = "labelConvertProcessStatus";
            this.labelConvertProcessStatus.Size = new System.Drawing.Size(584, 429);
            this.labelConvertProcessStatus.TabIndex = 0;
            this.labelConvertProcessStatus.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // panelDragAndDropInformation
            // 
            this.panelDragAndDropInformation.Controls.Add(this.panel3);
            this.panelDragAndDropInformation.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panelDragAndDropInformation.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.panelDragAndDropInformation.Location = new System.Drawing.Point(0, 0);
            this.panelDragAndDropInformation.Name = "panelDragAndDropInformation";
            this.panelDragAndDropInformation.Size = new System.Drawing.Size(584, 429);
            this.panelDragAndDropInformation.TabIndex = 4;
            this.panelDragAndDropInformation.Visible = false;
            // 
            // panel3
            // 
            this.panel3.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.panel3.Controls.Add(this.InfoLabel_1);
            this.panel3.Controls.Add(this.InfoLabel_2);
            this.panel3.Location = new System.Drawing.Point(-10, 167);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(614, 101);
            this.panel3.TabIndex = 2;
            // 
            // InfoLabel_1
            // 
            this.InfoLabel_1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.InfoLabel_1.AutoSize = true;
            this.InfoLabel_1.Location = new System.Drawing.Point(131, 0);
            this.InfoLabel_1.Name = "InfoLabel_1";
            this.InfoLabel_1.Size = new System.Drawing.Size(350, 31);
            this.InfoLabel_1.TabIndex = 0;
            this.InfoLabel_1.Text = "Отпустите кнопку мыши,";
            // 
            // InfoLabel_2
            // 
            this.InfoLabel_2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.InfoLabel_2.AutoSize = true;
            this.InfoLabel_2.Location = new System.Drawing.Point(24, 46);
            this.InfoLabel_2.Name = "InfoLabel_2";
            this.InfoLabel_2.Size = new System.Drawing.Size(561, 31);
            this.InfoLabel_2.TabIndex = 1;
            this.InfoLabel_2.Text = "чтобы завершить перемещение файлов!";
            // 
            // MainWindow
            // 
            this.AllowDrop = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(584, 429);
            this.Controls.Add(this.MainPanel);
            this.Controls.Add(this.panelConvertFilesStatus);
            this.Controls.Add(this.panelDragAndDropInformation);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Margin = new System.Windows.Forms.Padding(4);
            this.MinimumSize = new System.Drawing.Size(600, 400);
            this.Name = "MainWindow";
            this.Text = "Xlsx metrics converter";
            this.DragDrop += new System.Windows.Forms.DragEventHandler(this.MainWindow_DragDrop);
            this.DragEnter += new System.Windows.Forms.DragEventHandler(this.MainWindow_DragEnter);
            this.DragLeave += new System.EventHandler(this.MainWindow_DragLeave);
            this.groupBox1.ResumeLayout(false);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.tableLayout_TargetDir.ResumeLayout(false);
            this.tableLayout_TargetDir.PerformLayout();
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel2.PerformLayout();
            this.MainPanel.ResumeLayout(false);
            this.panelConvertFilesStatus.ResumeLayout(false);
            this.panelDragAndDropInformation.ResumeLayout(false);
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton radioSaveMode_NewFile;
        private System.Windows.Forms.RadioButton radioSaveMode_NewPage;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.RadioButton radioSaveMode_OneFileManyPages;
        private System.Windows.Forms.RadioButton radioSaveMode_OneFileOnePage;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.ListBox fileList;
        private System.Windows.Forms.Panel MainPanel;
        private System.Windows.Forms.Panel panelDragAndDropInformation;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Label InfoLabel_1;
        private System.Windows.Forms.Label InfoLabel_2;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Button buttonDoing;
        private System.Windows.Forms.Button buttonAddFiles;
        private System.Windows.Forms.TableLayoutPanel tableLayout_TargetDir;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button buttonSetSaveResultCurrentDir;
        private System.Windows.Forms.TextBox textBox_TargetDir;
        private System.Windows.Forms.Panel panelConvertFilesStatus;
        private System.Windows.Forms.Label labelConvertProcessStatus;
        private System.Windows.Forms.Button buttonConvertProcessOk;
    }
}

