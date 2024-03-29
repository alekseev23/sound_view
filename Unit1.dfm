object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Sound View'
  ClientHeight = 711
  ClientWidth = 1115
  Color = clBtnFace
  Constraints.MinHeight = 500
  Constraints.MinWidth = 1000
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  TextHeight = 13
  object StatusBar1: TStatusBar
    Left = 0
    Top = 616
    Width = 1115
    Height = 19
    Panels = <
      item
        Alignment = taCenter
        Width = 300
      end
      item
        Alignment = taCenter
        Width = 250
      end
      item
        Alignment = taCenter
        Width = 170
      end
      item
        Width = 50
      end>
    ExplicitTop = 615
    ExplicitWidth = 1111
  end
  object PageControl1: TPageControl
    AlignWithMargins = True
    Left = 3
    Top = 3
    Width = 1109
    Height = 545
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 1
    OnChange = PageControl1Change
    ExplicitWidth = 1105
    ExplicitHeight = 544
    object TabSheet1: TTabSheet
      Caption = #1054#1075#1080#1073#1072#1102#1097#1072#1103', '#1087#1072#1082#1077#1090#1099', '#1079#1074#1091#1082#1086#1074#1099#1077' '#1076#1072#1085#1085#1099#1077
      object PaintBox1: TPaintBox
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 1095
        Height = 494
        Align = alClient
        OnMouseDown = PaintBox1MouseDown
        OnMouseMove = PaintBox1MouseMove
        OnPaint = PaintBox1Paint
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 105
        ExplicitHeight = 105
      end
      object ScrollBar1: TScrollBar
        Left = 0
        Top = 500
        Width = 1101
        Height = 17
        Align = alBottom
        PageSize = 0
        TabOrder = 0
        OnChange = ScrollBar1Change
        ExplicitTop = 499
        ExplicitWidth = 1097
      end
    end
    object TabSheet2: TTabSheet
      Caption = #1055#1072#1082#1077#1090#1099', '#1087#1072#1091#1079#1099', '#1072#1084#1087#1083#1080#1090#1091#1076#1099
      ImageIndex = 1
      object PaintBox2: TPaintBox
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 1095
        Height = 494
        Align = alClient
        OnMouseDown = PaintBox2MouseDown
        OnMouseMove = PaintBox2MouseMove
        OnPaint = PaintBox2Paint
        ExplicitLeft = 496
        ExplicitTop = 272
        ExplicitWidth = 105
        ExplicitHeight = 105
      end
      object ScrollBar2: TScrollBar
        Left = 0
        Top = 500
        Width = 1101
        Height = 17
        Align = alBottom
        PageSize = 0
        TabOrder = 0
        OnChange = ScrollBar2Change
      end
    end
    object TabSheet3: TTabSheet
      Caption = #1058#1072#1073#1083#1080#1094#1072' '#1087#1072#1082#1077#1090#1086#1074
      ImageIndex = 2
      object StringGrid1: TStringGrid
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 1095
        Height = 470
        Align = alClient
        ColCount = 12
        DefaultColWidth = 70
        DefaultRowHeight = 18
        RowCount = 2
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goFixedRowDefAlign]
        TabOrder = 0
        OnClick = StringGrid1Click
      end
      object Panel2: TPanel
        Left = 0
        Top = 476
        Width = 1101
        Height = 41
        Align = alBottom
        BevelOuter = bvNone
        TabOrder = 1
        object BitBtn2: TBitBtn
          AlignWithMargins = True
          Left = 247
          Top = 3
          Width = 154
          Height = 35
          Align = alLeft
          Caption = #1055#1086#1080#1089#1082' '#1087#1086#1093#1086#1078#1080#1093' '#1087#1072#1082#1077#1090#1086#1074
          TabOrder = 0
          OnClick = BitBtn2Click
        end
        object BitBtn3: TBitBtn
          AlignWithMargins = True
          Left = 3
          Top = 3
          Width = 238
          Height = 35
          Align = alLeft
          Caption = #1057#1086#1079#1076#1072#1090#1100' '#1073#1072#1079#1091' '#1089#1087#1077#1082#1090#1088#1086#1074' '#1074#1089#1077#1093' '#1087#1072#1082#1077#1090#1086#1074
          TabOrder = 1
          OnClick = BitBtn3Click
        end
      end
    end
    object TabSheet4: TTabSheet
      Caption = #1043#1080#1089#1090#1086#1075#1088#1072#1084#1084#1099' '#1087#1072#1082#1077#1090#1086#1074
      ImageIndex = 3
      object PageControl2: TPageControl
        Left = 0
        Top = 0
        Width = 1101
        Height = 1101
        ActivePage = TabSheet5
        MultiLine = True
        TabOrder = 0
        TabPosition = tpBottom
        object TabSheet5: TTabSheet
          Caption = #1044#1083#1080#1085#1099' '#1087#1072#1082#1077#1090#1086#1074
          object ScrollBox1: TScrollBox
            Left = 0
            Top = 0
            Width = 1093
            Height = 1075
            Align = alClient
            TabOrder = 0
            object Image1: TImage
              Left = 3
              Top = 3
              Width = 105
              Height = 105
            end
          end
        end
        object TabSheet6: TTabSheet
          Caption = #1055#1072#1091#1079#1099
          ImageIndex = 1
          object ScrollBox2: TScrollBox
            AlignWithMargins = True
            Left = 3
            Top = 3
            Width = 1087
            Height = 1069
            Align = alClient
            TabOrder = 0
            object Image2: TImage
              Left = 3
              Top = 3
              Width = 105
              Height = 105
            end
          end
        end
        object TabSheet7: TTabSheet
          Caption = #1055#1086#1079#1080#1094#1080#1103' '#1084#1072#1082#1089#1080#1084#1072#1083#1100#1085#1086#1081' '#1072#1084#1087#1083#1080#1090#1091#1076#1099
          ImageIndex = 2
          object ScrollBox3: TScrollBox
            AlignWithMargins = True
            Left = 3
            Top = 3
            Width = 1087
            Height = 1069
            Align = alClient
            TabOrder = 0
            object Image3: TImage
              Left = 3
              Top = 3
              Width = 105
              Height = 105
            end
          end
        end
      end
    end
    object TabSheet8: TTabSheet
      Caption = #1055#1086#1093#1086#1078#1080#1077' '#1087#1072#1082#1077#1090#1099
      ImageIndex = 4
      object PaintBox3: TPaintBox
        AlignWithMargins = True
        Left = 3
        Top = 287
        Width = 1095
        Height = 227
        Align = alClient
        OnPaint = PaintBox3Paint
        ExplicitLeft = 496
        ExplicitTop = 216
        ExplicitWidth = 105
        ExplicitHeight = 105
      end
      object GroupBox3: TGroupBox
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 1095
        Height = 278
        Align = alTop
        Caption = #1057#1087#1080#1089#1086#1082' '#1085#1072#1080#1073#1086#1083#1077#1077' '#1087#1086#1093#1086#1078#1080#1093' '#1087#1072#1082#1077#1090#1086#1074' ('#1087#1077#1088#1074#1099#1081' - '#1086#1073#1088#1072#1079#1077#1094')'
        TabOrder = 0
        object StringGrid2: TStringGrid
          AlignWithMargins = True
          Left = 5
          Top = 18
          Width = 1085
          Height = 255
          Align = alClient
          ColCount = 14
          DefaultRowHeight = 18
          RowCount = 12
          TabOrder = 0
          OnClick = StringGrid2Click
        end
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 551
    Width = 1115
    Height = 65
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 2
    ExplicitTop = 550
    ExplicitWidth = 1111
    object GroupBox1: TGroupBox
      AlignWithMargins = True
      Left = 684
      Top = 3
      Width = 205
      Height = 59
      Align = alRight
      Caption = #1043#1088#1086#1084#1082#1086#1089#1090#1100
      TabOrder = 0
      ExplicitLeft = 680
      object TrackBar1: TTrackBar
        AlignWithMargins = True
        Left = 3
        Top = 20
        Width = 150
        Height = 36
        Hint = #1043#1088#1086#1084#1082#1086#1089#1090#1100
        Max = 100
        ParentShowHint = False
        Position = 100
        ShowHint = True
        TabOrder = 0
        OnChange = TrackBar1Change
      end
      object Edit1: TEdit
        Left = 152
        Top = 24
        Width = 41
        Height = 21
        ReadOnly = True
        TabOrder = 1
        Text = 'Edit1'
      end
    end
    object GroupBox2: TGroupBox
      AlignWithMargins = True
      Left = 895
      Top = 3
      Width = 217
      Height = 59
      Align = alRight
      Caption = #1055#1088#1086#1076#1086#1083#1078#1080#1090#1077#1083#1100#1085#1086#1089#1090#1100
      TabOrder = 1
      ExplicitLeft = 891
      object TrackBar2: TTrackBar
        AlignWithMargins = True
        Left = 0
        Top = 19
        Width = 150
        Height = 59
        Hint = #1055#1088#1086#1076#1086#1083#1078#1080#1090#1077#1083#1100#1085#1086#1089#1090#1100
        Max = 2000
        Min = 10
        ParentShowHint = False
        Position = 500
        ShowHint = True
        TabOrder = 0
        OnChange = TrackBar2Change
      end
      object Edit2: TEdit
        Left = 156
        Top = 24
        Width = 49
        Height = 21
        ReadOnly = True
        TabOrder = 1
        Text = 'Edit2'
      end
    end
    object Panel3: TPanel
      Left = 7
      Top = 3
      Width = 314
      Height = 41
      BevelOuter = bvNone
      TabOrder = 2
      object BitBtn1: TBitBtn
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 173
        Height = 35
        Align = alLeft
        Caption = #1040#1085#1072#1083#1080#1079' '#1080#1079#1084#1077#1085#1077#1085#1080#1081' '#1089#1087#1077#1082#1090#1088#1072
        TabOrder = 0
      end
    end
  end
  object StatusBar2: TStatusBar
    Left = 0
    Top = 635
    Width = 1115
    Height = 19
    Panels = <
      item
        Alignment = taCenter
        Width = 200
      end
      item
        Alignment = taCenter
        Width = 200
      end
      item
        Alignment = taCenter
        Width = 200
      end
      item
        Alignment = taCenter
        Width = 200
      end
      item
        Width = 50
      end>
    Visible = False
    ExplicitTop = 634
    ExplicitWidth = 1111
  end
  object StatusBar3: TStatusBar
    Left = 0
    Top = 654
    Width = 1115
    Height = 19
    Panels = <>
    SimpleText = #1044#1074#1086#1081#1085#1086#1081' '#1097#1077#1083#1095#1086#1082' '#1084#1099#1096#1082#1086#1081' '#1087#1086' '#1087#1072#1082#1077#1090#1091' '#1095#1090#1086#1073#1099' '#1087#1088#1086#1080#1075#1088#1072#1090#1100' '#1077#1075#1086
    ExplicitTop = 653
    ExplicitWidth = 1111
  end
  object StatusBar4: TStatusBar
    Left = 0
    Top = 673
    Width = 1115
    Height = 19
    Panels = <>
    ExplicitTop = 672
    ExplicitWidth = 1111
  end
  object StatusBar5: TStatusBar
    Left = 0
    Top = 692
    Width = 1115
    Height = 19
    Panels = <
      item
        Alignment = taCenter
        Width = 400
      end
      item
        Alignment = taCenter
        Width = 400
      end
      item
        Width = 50
      end>
    ExplicitTop = 691
    ExplicitWidth = 1111
  end
  object MainMenu1: TMainMenu
    Left = 264
    Top = 96
    object N1: TMenuItem
      Caption = #1060#1072#1081#1083
      object N3: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100
        ShortCut = 16463
        OnClick = N3Click
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object N5: TMenuItem
        Caption = #1042#1099#1093#1086#1076
        OnClick = N5Click
      end
    end
    object N6: TMenuItem
      Caption = #1047#1074#1091#1082#1086#1074#1099#1077' '#1076#1072#1085#1085#1099#1077
      object N7: TMenuItem
        AutoCheck = True
        Caption = #1047#1074#1091#1082#1086#1074#1099#1077' '#1076#1072#1085#1085#1099#1077
        Checked = True
        ShortCut = 113
        OnClick = N7Click
      end
      object N8: TMenuItem
        AutoCheck = True
        Caption = #1055#1077#1088#1074#1072#1103' '#1087#1088#1086#1080#1079#1074#1086#1076#1085#1072#1103
        Checked = True
        ShortCut = 114
        OnClick = N8Click
      end
      object N9: TMenuItem
        AutoCheck = True
        Caption = #1042#1090#1086#1088#1072#1103' '#1087#1088#1086#1080#1079#1074#1086#1076#1085#1072#1103
        Checked = True
        ShortCut = 115
        OnClick = N9Click
      end
      object N10: TMenuItem
        AutoCheck = True
        Caption = #1058#1088#1077#1090#1100#1103' '#1087#1088#1086#1080#1079#1074#1086#1076#1085#1072#1103
        Checked = True
        ShortCut = 116
        OnClick = N10Click
      end
      object N11: TMenuItem
        Caption = '-'
      end
      object N12: TMenuItem
        Caption = #1055#1086#1082#1072#1079#1072#1090#1100' '#1074#1089#1105
        ShortCut = 117
        OnClick = N12Click
      end
      object N13: TMenuItem
        Caption = #1057#1082#1088#1099#1090#1100' '#1074#1089#1105
        ShortCut = 118
        OnClick = N13Click
      end
    end
    object N2: TMenuItem
      Caption = #1055#1086#1084#1086#1097#1100
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = #1040#1091#1076#1080#1086' '#1092#1072#1081#1083#1099' (*.wav;*.mp3; *.ogg)|*.wav;*.mp3; *.ogg'
    Left = 120
    Top = 104
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 500
    OnTimer = Timer1Timer
    Left = 720
    Top = 96
  end
  object Timer2: TTimer
    Enabled = False
    OnTimer = Timer2Timer
    Left = 872
    Top = 280
  end
  object Timer3: TTimer
    Enabled = False
    Left = 944
    Top = 136
  end
end
