namespace WindowsFormsApp1
{
    partial class Form1
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
            this.psyDataGridView = new System.Windows.Forms.DataGridView();
            this.tsDataGridView = new System.Windows.Forms.DataGridView();
            this.updateButton = new System.Windows.Forms.Button();
            this.ConnectButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.psyDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tsDataGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // psyDataGridView
            // 
            this.psyDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.psyDataGridView.Location = new System.Drawing.Point(47, 38);
            this.psyDataGridView.Name = "psyDataGridView";
            this.psyDataGridView.RowHeadersWidth = 49;
            this.psyDataGridView.RowTemplate.Height = 24;
            this.psyDataGridView.Size = new System.Drawing.Size(560, 223);
            this.psyDataGridView.TabIndex = 0;
            // 
            // tsDataGridView
            // 
            this.tsDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.tsDataGridView.Location = new System.Drawing.Point(787, 38);
            this.tsDataGridView.Name = "tsDataGridView";
            this.tsDataGridView.RowHeadersWidth = 49;
            this.tsDataGridView.RowTemplate.Height = 24;
            this.tsDataGridView.Size = new System.Drawing.Size(499, 223);
            this.tsDataGridView.TabIndex = 1;
            // 
            // updateButton
            // 
            this.updateButton.Location = new System.Drawing.Point(649, 345);
            this.updateButton.Name = "updateButton";
            this.updateButton.Size = new System.Drawing.Size(75, 23);
            this.updateButton.TabIndex = 2;
            this.updateButton.Text = "Update";
            this.updateButton.UseVisualStyleBackColor = true;
            this.updateButton.Click += new System.EventHandler(this.UpdateButton_Click);
            // 
            // ConnectButton
            // 
            this.ConnectButton.Location = new System.Drawing.Point(450, 345);
            this.ConnectButton.Name = "ConnectButton";
            this.ConnectButton.Size = new System.Drawing.Size(75, 23);
            this.ConnectButton.TabIndex = 3;
            this.ConnectButton.Text = "Connect";
            this.ConnectButton.UseVisualStyleBackColor = true;
            this.ConnectButton.Click += new System.EventHandler(this.ConnectButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1483, 450);
            this.Controls.Add(this.ConnectButton);
            this.Controls.Add(this.updateButton);
            this.Controls.Add(this.tsDataGridView);
            this.Controls.Add(this.psyDataGridView);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.psyDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tsDataGridView)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView psyDataGridView;
        private System.Windows.Forms.DataGridView tsDataGridView;
        private System.Windows.Forms.Button updateButton;
        private System.Windows.Forms.Button ConnectButton;
    }
}

