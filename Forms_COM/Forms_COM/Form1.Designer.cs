
namespace Forms_COM
{
    partial class Form1
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
            this.components = new System.ComponentModel.Container();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.toolStripMenuStart = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuStop = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuPause = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuContinue = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuProperty = new System.Windows.Forms.ToolStripMenuItem();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.ColumnName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnStatus = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnType = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.contextMenuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.SuspendLayout();
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuStart,
            this.toolStripMenuStop,
            this.toolStripMenuPause,
            this.toolStripMenuContinue,
            this.toolStripMenuProperty});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(160, 114);
            this.contextMenuStrip1.Opening += new System.ComponentModel.CancelEventHandler(this.contextMenuStrip1_Opening);
            // 
            // toolStripMenuStart
            // 
            this.toolStripMenuStart.Enabled = false;
            this.toolStripMenuStart.Name = "toolStripMenuStart";
            this.toolStripMenuStart.Size = new System.Drawing.Size(180, 22);
            this.toolStripMenuStart.Text = "Запустить";
            this.toolStripMenuStart.Click += new System.EventHandler(this.toolStripMenuStart_Click);
            // 
            // toolStripMenuStop
            // 
            this.toolStripMenuStop.Enabled = false;
            this.toolStripMenuStop.Name = "toolStripMenuStop";
            this.toolStripMenuStop.Size = new System.Drawing.Size(180, 22);
            this.toolStripMenuStop.Text = "Остановить";
            this.toolStripMenuStop.Click += new System.EventHandler(this.toolStripMenuStop_Click);
            // 
            // toolStripMenuPause
            // 
            this.toolStripMenuPause.Enabled = false;
            this.toolStripMenuPause.Name = "toolStripMenuPause";
            this.toolStripMenuPause.Size = new System.Drawing.Size(180, 22);
            this.toolStripMenuPause.Text = "Приостановить";
            this.toolStripMenuPause.Click += new System.EventHandler(this.toolStripMenuPause_Click);
            // 
            // toolStripMenuContinue
            // 
            this.toolStripMenuContinue.Enabled = false;
            this.toolStripMenuContinue.Name = "toolStripMenuContinue";
            this.toolStripMenuContinue.Size = new System.Drawing.Size(180, 22);
            this.toolStripMenuContinue.Text = "Продолжить";
            this.toolStripMenuContinue.Click += new System.EventHandler(this.toolStripMenuContinue_Click);
            // 
            // toolStripMenuProperty
            // 
            this.toolStripMenuProperty.Name = "toolStripMenuProperty";
            this.toolStripMenuProperty.Size = new System.Drawing.Size(180, 22);
            this.toolStripMenuProperty.Text = "Свойства";
            this.toolStripMenuProperty.Click += new System.EventHandler(this.toolStripMenuProperty_Click);
            // 
            // dataGridView1
            // 
            this.dataGridView1.AllowUserToAddRows = false;
            this.dataGridView1.AllowUserToDeleteRows = false;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.ColumnName,
            this.ColumnStatus,
            this.ColumnType});
            this.dataGridView1.ContextMenuStrip = this.contextMenuStrip1;
            this.dataGridView1.Location = new System.Drawing.Point(12, 12);
            this.dataGridView1.MultiSelect = false;
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.ReadOnly = true;
            this.dataGridView1.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView1.Size = new System.Drawing.Size(759, 426);
            this.dataGridView1.TabIndex = 2;
            // 
            // ColumnName
            // 
            this.ColumnName.Frozen = true;
            this.ColumnName.HeaderText = "Имя";
            this.ColumnName.Name = "ColumnName";
            this.ColumnName.ReadOnly = true;
            this.ColumnName.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.ColumnName.Width = 500;
            // 
            // ColumnStatus
            // 
            this.ColumnStatus.Frozen = true;
            this.ColumnStatus.HeaderText = "Состояние";
            this.ColumnStatus.Name = "ColumnStatus";
            this.ColumnStatus.ReadOnly = true;
            this.ColumnStatus.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            // 
            // ColumnType
            // 
            this.ColumnType.Frozen = true;
            this.ColumnType.HeaderText = "Тип";
            this.ColumnType.Name = "ColumnType";
            this.ColumnType.ReadOnly = true;
            this.ColumnType.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(783, 450);
            this.Controls.Add(this.dataGridView1);
            this.Name = "Form1";
            this.Text = "Services";
            this.contextMenuStrip1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuStart;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuStop;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuPause;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuContinue;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuProperty;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnName;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnStatus;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnType;
    }
}

