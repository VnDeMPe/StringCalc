
namespace FrontEnd_Calc
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.stringInputBox = new System.Windows.Forms.TextBox();
            this.stringOutputBox = new System.Windows.Forms.TextBox();
            this.buttonCalculateIt = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.listPastResults = new System.Windows.Forms.ListBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.listOutputConsole = new System.Windows.Forms.TextBox();
            this.authorLabel = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Imprint MT Shadow", 36F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.label1.Location = new System.Drawing.Point(262, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(415, 57);
            this.label1.TabIndex = 0;
            this.label1.Text = "String ICalculator";
            // 
            // stringInputBox
            // 
            this.stringInputBox.Location = new System.Drawing.Point(16, 242);
            this.stringInputBox.Name = "stringInputBox";
            this.stringInputBox.Size = new System.Drawing.Size(211, 23);
            this.stringInputBox.TabIndex = 1;
            // 
            // stringOutputBox
            // 
            this.stringOutputBox.Location = new System.Drawing.Point(275, 242);
            this.stringOutputBox.Name = "stringOutputBox";
            this.stringOutputBox.ReadOnly = true;
            this.stringOutputBox.Size = new System.Drawing.Size(219, 23);
            this.stringOutputBox.TabIndex = 2;
            // 
            // buttonCalculateIt
            // 
            this.buttonCalculateIt.Location = new System.Drawing.Point(16, 291);
            this.buttonCalculateIt.Name = "buttonCalculateIt";
            this.buttonCalculateIt.Size = new System.Drawing.Size(75, 23);
            this.buttonCalculateIt.TabIndex = 3;
            this.buttonCalculateIt.Text = "Calculate!";
            this.buttonCalculateIt.UseVisualStyleBackColor = true;
            this.buttonCalculateIt.Click += new System.EventHandler(this.button1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Segoe UI", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.label2.Location = new System.Drawing.Point(244, 240);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(25, 25);
            this.label2.TabIndex = 4;
            this.label2.Text = "=";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(275, 268);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(39, 15);
            this.label3.TabIndex = 5;
            this.label3.Text = "Result";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(16, 267);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(113, 15);
            this.label4.TabIndex = 6;
            this.label4.Text = "Type the string here!";
            // 
            // listPastResults
            // 
            this.listPastResults.FormattingEnabled = true;
            this.listPastResults.ItemHeight = 15;
            this.listPastResults.Location = new System.Drawing.Point(16, 326);
            this.listPastResults.Name = "listPastResults";
            this.listPastResults.Size = new System.Drawing.Size(478, 94);
            this.listPastResults.TabIndex = 7;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(16, 423);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(66, 15);
            this.label5.TabIndex = 8;
            this.label5.Text = "Past results";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(518, 422);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(91, 15);
            this.label6.TabIndex = 10;
            this.label6.Text = "Output Console";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(19, 87);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(72, 15);
            this.label7.TabIndex = 11;
            this.label7.Text = "Instructions:";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(19, 111);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(86, 15);
            this.label8.TabIndex = 12;
            this.label8.Text = "\'+\' for addition";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(19, 126);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(104, 15);
            this.label9.TabIndex = 13;
            this.label9.Text = "\'-\' for substraction";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(19, 141);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(113, 15);
            this.label10.TabIndex = 14;
            this.label10.Text = "\'*\' for multiplication";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(19, 156);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(80, 15);
            this.label11.TabIndex = 15;
            this.label11.Text = "\'/\' for division";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(19, 171);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(275, 15);
            this.label12.TabIndex = 16;
            this.label12.Text = "\'^\' for exponentiation (example: 2^5 will return 32)";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(19, 186);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(230, 15);
            this.label13.TabIndex = 17;
            this.label13.Text = "\'$\' for rooting (example: 32$5 will return 2)";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(19, 204);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(259, 15);
            this.label14.TabIndex = 18;
            this.label14.Text = " Example Input: (2 + 3) * ((4+ 5+ 6)*2) * 3 -128$7";
            // 
            // listOutputConsole
            // 
            this.listOutputConsole.Location = new System.Drawing.Point(518, 103);
            this.listOutputConsole.Multiline = true;
            this.listOutputConsole.Name = "listOutputConsole";
            this.listOutputConsole.ReadOnly = true;
            this.listOutputConsole.Size = new System.Drawing.Size(456, 316);
            this.listOutputConsole.TabIndex = 19;
            // 
            // authorLabel
            // 
            this.authorLabel.AutoSize = true;
            this.authorLabel.Font = new System.Drawing.Font("Modern No. 20", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.authorLabel.Location = new System.Drawing.Point(879, 433);
            this.authorLabel.Name = "authorLabel";
            this.authorLabel.Size = new System.Drawing.Size(109, 13);
            this.authorLabel.TabIndex = 20;
            this.authorLabel.Text = "by Marcin Petschke, 2021";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Font = new System.Drawing.Font("Imprint MT Shadow", 12F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point);
            this.label15.Location = new System.Drawing.Point(244, 66);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(452, 19);
            this.label15.TabIndex = 21;
            this.label15.Text = "No worries if you make some syntax error, it will be autocorrected!";
            // 
            // Form1
            // 
            this.AcceptButton = this.buttonCalculateIt;
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(991, 455);
            this.Controls.Add(this.label15);
            this.Controls.Add(this.authorLabel);
            this.Controls.Add(this.listOutputConsole);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.listPastResults);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.buttonCalculateIt);
            this.Controls.Add(this.stringOutputBox);
            this.Controls.Add(this.stringInputBox);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "String Calculator";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox stringInputBox;
        private System.Windows.Forms.TextBox stringOutputBox;
        private System.Windows.Forms.Button buttonCalculateIt;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ListBox listPastResults;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.TextBox listOutputConsole;
        private System.Windows.Forms.Label authorLabel;
        private System.Windows.Forms.Label label15;
    }
}

