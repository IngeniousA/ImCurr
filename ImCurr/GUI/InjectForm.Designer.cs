namespace UI6
{
    partial class InjectForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.openFile = new System.Windows.Forms.OpenFileDialog();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.injBtn = new System.Windows.Forms.Button();
            this.selrecBtn = new System.Windows.Forms.Button();
            this.selinjBtn = new System.Windows.Forms.Button();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.label3 = new System.Windows.Forms.Label();
            this.ejBtn = new System.Windows.Forms.Button();
            this.selejBtn = new System.Windows.Forms.Button();
            this.destBox = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.SuspendLayout();
            // 
            // openFile
            // 
            this.openFile.Filter = "All files| *.*|Encrypted files (*.scsn, *.icf, *.ic6) | *.scsn, *.icf, *.ic6|Cont" +
    "ainers (*.ict, i6c) | *.ict, *.i6c";
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(330, 169);
            this.tabControl1.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(32)))), ((int)(((byte)(32)))), ((int)(((byte)(32)))));
            this.tabPage1.Controls.Add(this.label2);
            this.tabPage1.Controls.Add(this.label1);
            this.tabPage1.Controls.Add(this.injBtn);
            this.tabPage1.Controls.Add(this.selrecBtn);
            this.tabPage1.Controls.Add(this.selinjBtn);
            this.tabPage1.Font = new System.Drawing.Font("Consolas", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.tabPage1.ForeColor = System.Drawing.Color.White;
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(322, 143);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Inject";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(165, 69);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(79, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "NOT SELECTED";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(165, 27);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(79, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "NOT SELECTED";
            // 
            // injBtn
            // 
            this.injBtn.Enabled = false;
            this.injBtn.Font = new System.Drawing.Font("Consolas", 9.75F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.injBtn.ForeColor = System.Drawing.Color.Black;
            this.injBtn.Location = new System.Drawing.Point(8, 111);
            this.injBtn.Name = "injBtn";
            this.injBtn.Size = new System.Drawing.Size(306, 23);
            this.injBtn.TabIndex = 3;
            this.injBtn.Text = "Inject";
            this.injBtn.UseVisualStyleBackColor = true;
            this.injBtn.Click += new System.EventHandler(this.injBtn_Click);
            // 
            // selrecBtn
            // 
            this.selrecBtn.Enabled = false;
            this.selrecBtn.ForeColor = System.Drawing.Color.Black;
            this.selrecBtn.Location = new System.Drawing.Point(8, 64);
            this.selrecBtn.Name = "selrecBtn";
            this.selrecBtn.Size = new System.Drawing.Size(150, 23);
            this.selrecBtn.TabIndex = 2;
            this.selrecBtn.Text = "Select recipient file";
            this.selrecBtn.UseVisualStyleBackColor = true;
            this.selrecBtn.Click += new System.EventHandler(this.selrecBtn_Click);
            // 
            // selinjBtn
            // 
            this.selinjBtn.ForeColor = System.Drawing.Color.Black;
            this.selinjBtn.Location = new System.Drawing.Point(8, 22);
            this.selinjBtn.Name = "selinjBtn";
            this.selinjBtn.Size = new System.Drawing.Size(150, 23);
            this.selinjBtn.TabIndex = 1;
            this.selinjBtn.Text = "Select injection file";
            this.selinjBtn.UseVisualStyleBackColor = true;
            this.selinjBtn.Click += new System.EventHandler(this.selinjBtn_Click);
            // 
            // tabPage2
            // 
            this.tabPage2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(32)))), ((int)(((byte)(32)))), ((int)(((byte)(32)))));
            this.tabPage2.Controls.Add(this.label4);
            this.tabPage2.Controls.Add(this.destBox);
            this.tabPage2.Controls.Add(this.label3);
            this.tabPage2.Controls.Add(this.ejBtn);
            this.tabPage2.Controls.Add(this.selejBtn);
            this.tabPage2.Font = new System.Drawing.Font("Consolas", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(322, 143);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Eject";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.ForeColor = System.Drawing.Color.White;
            this.label3.Location = new System.Drawing.Point(164, 25);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(79, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "NOT SELECTED";
            // 
            // ejBtn
            // 
            this.ejBtn.Enabled = false;
            this.ejBtn.Font = new System.Drawing.Font("Consolas", 9.75F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.ejBtn.ForeColor = System.Drawing.Color.Black;
            this.ejBtn.Location = new System.Drawing.Point(8, 111);
            this.ejBtn.Name = "ejBtn";
            this.ejBtn.Size = new System.Drawing.Size(306, 23);
            this.ejBtn.TabIndex = 4;
            this.ejBtn.Text = "Eject";
            this.ejBtn.UseVisualStyleBackColor = true;
            this.ejBtn.Click += new System.EventHandler(this.ejBtn_Click);
            // 
            // selejBtn
            // 
            this.selejBtn.ForeColor = System.Drawing.Color.Black;
            this.selejBtn.Location = new System.Drawing.Point(8, 20);
            this.selejBtn.Name = "selejBtn";
            this.selejBtn.Size = new System.Drawing.Size(150, 23);
            this.selejBtn.TabIndex = 3;
            this.selejBtn.Text = "Select injected file";
            this.selejBtn.UseVisualStyleBackColor = true;
            this.selejBtn.Click += new System.EventHandler(this.selejBtn_Click);
            // 
            // destBox
            // 
            this.destBox.Enabled = false;
            this.destBox.Location = new System.Drawing.Point(9, 72);
            this.destBox.Name = "destBox";
            this.destBox.Size = new System.Drawing.Size(149, 20);
            this.destBox.TabIndex = 6;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.ForeColor = System.Drawing.Color.White;
            this.label4.Location = new System.Drawing.Point(8, 56);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(139, 13);
            this.label4.TabIndex = 7;
            this.label4.Text = "Destination file name:";
            // 
            // InjectForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(32)))), ((int)(((byte)(32)))), ((int)(((byte)(32)))));
            this.ClientSize = new System.Drawing.Size(330, 169);
            this.Controls.Add(this.tabControl1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "InjectForm";
            this.Text = "Inject/Eject";
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.OpenFileDialog openFile;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Button injBtn;
        private System.Windows.Forms.Button selrecBtn;
        private System.Windows.Forms.Button selinjBtn;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button ejBtn;
        private System.Windows.Forms.Button selejBtn;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox destBox;
    }
}