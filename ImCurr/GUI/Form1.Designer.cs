namespace UI6
{
    partial class mainForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(mainForm));
            this.fileBtn = new System.Windows.Forms.Button();
            this.dirBtn = new System.Windows.Forms.Button();
            this.bpanel = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.actionBtn = new System.Windows.Forms.Button();
            this.pwdBox = new System.Windows.Forms.MaskedTextBox();
            this.nameBox = new System.Windows.Forms.TextBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.logBox = new System.Windows.Forms.ListBox();
            this.openFile = new System.Windows.Forms.OpenFileDialog();
            this.button1 = new System.Windows.Forms.Button();
            this.bpanel.SuspendLayout();
            this.panel2.SuspendLayout();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // fileBtn
            // 
            this.fileBtn.ForeColor = System.Drawing.Color.Black;
            this.fileBtn.Location = new System.Drawing.Point(10, 10);
            this.fileBtn.Name = "fileBtn";
            this.fileBtn.Size = new System.Drawing.Size(81, 23);
            this.fileBtn.TabIndex = 0;
            this.fileBtn.Text = "Open file";
            this.fileBtn.UseVisualStyleBackColor = true;
            this.fileBtn.Click += new System.EventHandler(this.fileBtn_Click);
            // 
            // dirBtn
            // 
            this.dirBtn.ForeColor = System.Drawing.Color.Black;
            this.dirBtn.Location = new System.Drawing.Point(97, 10);
            this.dirBtn.Name = "dirBtn";
            this.dirBtn.Size = new System.Drawing.Size(87, 23);
            this.dirBtn.TabIndex = 1;
            this.dirBtn.Text = "Open folder";
            this.dirBtn.UseVisualStyleBackColor = true;
            this.dirBtn.Click += new System.EventHandler(this.dirBtn_Click);
            // 
            // bpanel
            // 
            this.bpanel.Controls.Add(this.panel2);
            this.bpanel.Controls.Add(this.panel1);
            this.bpanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.bpanel.Location = new System.Drawing.Point(0, 0);
            this.bpanel.Name = "bpanel";
            this.bpanel.Size = new System.Drawing.Size(719, 44);
            this.bpanel.TabIndex = 2;
            // 
            // panel2
            // 
            this.panel2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel2.Controls.Add(this.button1);
            this.panel2.Controls.Add(this.actionBtn);
            this.panel2.Controls.Add(this.pwdBox);
            this.panel2.Controls.Add(this.nameBox);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(193, 0);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(526, 44);
            this.panel2.TabIndex = 3;
            // 
            // actionBtn
            // 
            this.actionBtn.Font = new System.Drawing.Font("Consolas", 8.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.actionBtn.ForeColor = System.Drawing.Color.Black;
            this.actionBtn.Location = new System.Drawing.Point(267, 9);
            this.actionBtn.Name = "actionBtn";
            this.actionBtn.Size = new System.Drawing.Size(131, 23);
            this.actionBtn.TabIndex = 2;
            this.actionBtn.Text = "No file selected";
            this.actionBtn.UseVisualStyleBackColor = true;
            this.actionBtn.Click += new System.EventHandler(this.actionBtn_Click);
            // 
            // pwdBox
            // 
            this.pwdBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pwdBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.pwdBox.ForeColor = System.Drawing.Color.Gray;
            this.pwdBox.Location = new System.Drawing.Point(140, 11);
            this.pwdBox.Name = "pwdBox";
            this.pwdBox.Size = new System.Drawing.Size(120, 20);
            this.pwdBox.TabIndex = 1;
            this.pwdBox.Text = "Password";
            this.pwdBox.TextChanged += new System.EventHandler(this.pwdBox_TextChanged);
            this.pwdBox.Enter += new System.EventHandler(this.pwdBox_Enter);
            this.pwdBox.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pwdBox_MouseUp);
            // 
            // nameBox
            // 
            this.nameBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.nameBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.nameBox.ForeColor = System.Drawing.Color.Gray;
            this.nameBox.Location = new System.Drawing.Point(11, 11);
            this.nameBox.Multiline = true;
            this.nameBox.Name = "nameBox";
            this.nameBox.Size = new System.Drawing.Size(120, 20);
            this.nameBox.TabIndex = 0;
            this.nameBox.Text = "Output file name";
            this.nameBox.TextChanged += new System.EventHandler(this.nameBox_TextChanged);
            this.nameBox.MouseUp += new System.Windows.Forms.MouseEventHandler(this.nameBox_MouseUp);
            // 
            // panel1
            // 
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Controls.Add(this.fileBtn);
            this.panel1.Controls.Add(this.dirBtn);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Left;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(193, 44);
            this.panel1.TabIndex = 2;
            // 
            // logBox
            // 
            this.logBox.BackColor = System.Drawing.Color.Black;
            this.logBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.logBox.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.logBox.Font = new System.Drawing.Font("Consolas", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.logBox.ForeColor = System.Drawing.Color.White;
            this.logBox.FormattingEnabled = true;
            this.logBox.Items.AddRange(new object[] {
            "Welcome to ImCurr 0.7!",
            "Please select file or folder to proceed..."});
            this.logBox.Location = new System.Drawing.Point(0, 47);
            this.logBox.Name = "logBox";
            this.logBox.Size = new System.Drawing.Size(719, 299);
            this.logBox.TabIndex = 3;
            // 
            // openFile
            // 
            this.openFile.Filter = "All files| *.*|Encrypted files (*.scsn, *.icf, *.ic6) | *.scsn, *.icf, *.ic6|Cont" +
    "ainers (*.ict, i6c) | *.ict, *.i6c";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(404, 9);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(109, 23);
            this.button1.TabIndex = 3;
            this.button1.Text = "Inject/Eject";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(32)))), ((int)(((byte)(32)))), ((int)(((byte)(32)))));
            this.ClientSize = new System.Drawing.Size(719, 346);
            this.Controls.Add(this.logBox);
            this.Controls.Add(this.bpanel);
            this.Font = new System.Drawing.Font("Consolas", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "mainForm";
            this.Text = "ImCurr 0.7";
            this.Load += new System.EventHandler(this.mainForm_Load);
            this.bpanel.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button fileBtn;
        private System.Windows.Forms.Button dirBtn;
        private System.Windows.Forms.Panel bpanel;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.MaskedTextBox pwdBox;
        private System.Windows.Forms.TextBox nameBox;
        private System.Windows.Forms.Button actionBtn;
        private System.Windows.Forms.ListBox logBox;
        private System.Windows.Forms.OpenFileDialog openFile;
        private System.Windows.Forms.Button button1;
    }
}

