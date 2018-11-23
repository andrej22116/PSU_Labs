using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CsWinFormGraphicsPanel.GraphicsPanel
{
    class GraphicsPanel : Panel
    {
        #region Свойства

        bool _painting = false;
        bool _needUpdatePoints = false;

        private Brush _fillBrush;
        private Pen _pen;
        private float _penWidth = 5;
        private Color _color = Color.Red;

        // Цвет заполнения фигур
        public Color FillColor {
            get => _color;
            set
            {
                _color = value;
                UpdatePen();
                _brushCreateMethod();
            }
        }

        public bool Antialiasing { get; set; }

        private bool _symetricPhigure;
        private Rectangle _phigureRect;
        private Point _beginPoint;
        private Point _endPoint;

        #endregion


        #region Буфферизация

        private Buffer _curentPaintBuffer;
        private BufferedGraphicsContext _currentContext = BufferedGraphicsManager.Current;
        private BufferedGraphics _resultImageBuffer;

        #endregion


        #region Установка свойств
        private delegate void BrushCreateMethod();
        private BrushCreateMethod _brushCreateMethod;

        public void UpdatePen()
        {
            _pen = new Pen(FillColor, _penWidth);
            _pen.StartCap = LineCap.Round;
            _pen.EndCap = LineCap.Round;
        }

        public void SetFillBrush()
        {
            _fillBrush = new SolidBrush(FillColor);
            _brushCreateMethod = SetFillBrush;
        }

        public void SetVerticalHatchBrush()
        {
            _fillBrush = new HatchBrush(HatchStyle.Vertical, FillColor);
            _brushCreateMethod = SetVerticalHatchBrush;
        }

        public void SetHorisontalHatchBrush()
        {
            _fillBrush = new HatchBrush(HatchStyle.Horizontal, FillColor);
            _brushCreateMethod = SetHorisontalHatchBrush;
        }
        #endregion


        #region Пользовательские возможности

        private delegate void DelegateNextPointSetMethod(Point nextPoint);
        private DelegateNextPointSetMethod _nextPointSetMethod;

        public GraphicsPanel()
        {
            _resultImageBuffer = _currentContext.Allocate(this.CreateGraphics(), this.ClientRectangle);
            _resultImageBuffer.Graphics.Clear(Color.White);
            Antialiasing = true;

            UpdatePen();
            SetFillBrush();

            SetStyle(ControlStyles.UserPaint, true);
            SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
            UpdateStyles();
        }

        public void BeginPaintLine(Point beginPoint)
        {
            CreateCurentBuffer();
            _drawMethod = DrawLine;
            _nextPointSetMethod = SetNextPointForLine;

            SetPaintParams(beginPoint);
        }

        public void BeginPaintEllipse(Point beginPoint, bool circle = false)
        {
            CreateCurentBuffer();
            _symetricPhigure = circle;
            _drawMethod = DrawEllipse;
            _nextPointSetMethod = SetNextPointForPhigure;

            SetPaintParams(beginPoint);
        }

        public void BeginPaintRectangle(Point beginPoint, bool square = false)
        {
            CreateCurentBuffer();
            _symetricPhigure = square;
            _drawMethod = DrawRectangle;
            _nextPointSetMethod = SetNextPointForPhigure;

            SetPaintParams(beginPoint);
        }

        public void UpdatePaint(Point nextPoint)
        {
            if ( _needUpdatePoints)
            {
                _needUpdatePoints = false;
                _nextPointSetMethod?.Invoke(nextPoint);
                this.Invalidate();
            }
        }

        public void EndPaint()
        {
            _resultImageBuffer.Graphics.DrawImage(_curentPaintBuffer.Bitmap, 0, 0);
            _curentPaintBuffer.Dispose();
            _painting = false;
            _needUpdatePoints = false;
        }

        private void CreateCurentBuffer()
        {
            _curentPaintBuffer = new Buffer(this.ClientRectangle);
            _curentPaintBuffer.Graphics.SmoothingMode = Antialiasing ? SmoothingMode.AntiAlias 
                                                                     : SmoothingMode.HighSpeed;
        }

        private void SetPaintParams(Point beginPoint)
        {
            _beginPoint = beginPoint;
            _endPoint = beginPoint;

            _needUpdatePoints = true;
            _painting = true;
        }

        private void SetNextPointForLine(Point nextPoint)
        {
            _beginPoint = _endPoint;
            _endPoint = nextPoint;
        }

        private void SetNextPointForPhigure(Point nextPoint)
        {
            _endPoint = nextPoint;

            int point_x = Math.Min(_beginPoint.X, _endPoint.X);
            int point_y = Math.Min(_beginPoint.Y, _endPoint.Y);
            int width = Math.Abs(_beginPoint.X - _endPoint.X);
            int height = Math.Abs(_beginPoint.Y - _endPoint.Y);

            _phigureRect = new Rectangle(point_x, point_y, width, height);

            if ( _symetricPhigure )
            {
                int minLength = Math.Min(width, height);
                _phigureRect.Width = minLength;
                _phigureRect.Height = _phigureRect.Width;

                _phigureRect.X = _phigureRect.X == _endPoint.X
                    ? _phigureRect.X + width - minLength
                    : _phigureRect.X;

                _phigureRect.Y = _phigureRect.Y == _endPoint.Y
                    ? _phigureRect.Y + height - minLength
                    : _phigureRect.Y;
            }
        }

        #endregion


        #region Процесс рисования

        private delegate void DelegateDrawMethod();
        private DelegateDrawMethod _drawMethod;


        protected override void OnPaint(PaintEventArgs e)
        {
            if ( _painting )
            {
                _drawMethod?.Invoke();
                e.Graphics.DrawImage(_curentPaintBuffer.Bitmap, 0, 0);
                _needUpdatePoints = true;
            }
        }


        protected override void OnPaintBackground(PaintEventArgs e)
        {
            _resultImageBuffer.Render(e.Graphics);
        }


        protected override void OnResize(EventArgs eventargs)
        {
            base.OnResize(eventargs);

            var rect = this.ClientRectangle;
            rect.Width = rect.Width > 0 ? rect.Width : 1;
            rect.Height = rect.Height > 0 ? rect.Height : 1;

            var newBuffer = _currentContext.Allocate(this.CreateGraphics(), rect);
            newBuffer.Graphics.Clear(Color.White);
            newBuffer.Graphics.SmoothingMode = Antialiasing ? SmoothingMode.AntiAlias 
                                                            : SmoothingMode.HighSpeed;

            _resultImageBuffer.Render(newBuffer.Graphics);
            _resultImageBuffer.Dispose();

            _resultImageBuffer = newBuffer;
        }

        private void DrawLine()
        {
            _curentPaintBuffer.Graphics.DrawLine(_pen, _beginPoint, _endPoint);
        }

        private void DrawEllipse()
        {
            _curentPaintBuffer.Graphics.Clear(Color.Transparent);
            _curentPaintBuffer.Graphics.DrawEllipse(_pen, _phigureRect);
        }

        private void DrawRectangle()
        {
            _curentPaintBuffer.Graphics.Clear(Color.Transparent);
            _curentPaintBuffer.Graphics.DrawRectangle(_pen, _phigureRect);
        }

        #endregion


        #region Обработка событий мыши

        public delegate void DelegateOnMouseEvent(MouseEventArgs e);

        public DelegateOnMouseEvent EventMouseButtonPressed;
        public DelegateOnMouseEvent EventMouseMove;
        public DelegateOnMouseEvent EventMouseButtonReleased;


        protected override void OnMouseDown(MouseEventArgs e)
        {
            EventMouseButtonPressed?.Invoke(e);

            BeginPaintEllipse(e.Location);
        }

        protected override void OnMouseMove(MouseEventArgs e)
        {
            EventMouseMove?.Invoke(e);

            if ( _painting ) { UpdatePaint(e.Location); }
        }

        protected override void OnMouseUp(MouseEventArgs e)
        {
            EventMouseButtonReleased?.Invoke(e);

            if (_painting) { EndPaint(); }
        }

        #endregion


        private class Buffer : IDisposable
        {
            private Bitmap bitmap;
            private Graphics graphics;

            public Bitmap Bitmap
            {
                get { return bitmap; }
            }

            public Graphics Graphics
            {
                get { return graphics; }
            }

            public Buffer(int width, int height)
            {
                makeBuffer(width, height);
            }

            public Buffer(Rectangle rect)
            {
                makeBuffer(rect.Width, rect.Height);
            }

            private void makeBuffer(int width, int height)
            {

                bitmap = new Bitmap(
                    width > 0 ? width : 1,
                    height > 0 ? height : 1,
                    System.Drawing.Imaging.PixelFormat.Format32bppArgb);
                bitmap.MakeTransparent();

                this.graphics = Graphics.FromImage(bitmap);
            }

            public void Dispose()
            {
                this.bitmap.Dispose();
                this.Graphics.Dispose();
            }
        }
    }
}
