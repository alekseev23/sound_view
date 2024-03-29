object Form4: TForm4
  Left = 0
  Top = 0
  Caption = 'FFT '#1072#1085#1072#1083#1080#1079
  ClientHeight = 707
  ClientWidth = 914
  Color = clBtnFace
  Constraints.MinHeight = 500
  Constraints.MinWidth = 830
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar1: TStatusBar
    Left = 0
    Top = 688
    Width = 914
    Height = 19
    Panels = <
      item
        Alignment = taCenter
        Width = 250
      end
      item
        Alignment = taCenter
        Width = 150
      end
      item
        Alignment = taCenter
        Width = 250
      end
      item
        Width = 50
      end>
  end
  object Panel1: TPanel
    Left = 0
    Top = 647
    Width = 914
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    object BitBtn1: TBitBtn
      AlignWithMargins = True
      Left = 3
      Top = 3
      Width = 126
      Height = 35
      Align = alLeft
      Caption = #1055#1088#1077#1076#1099#1076#1091#1097#1080#1081' '#1087#1072#1082#1077#1090
      TabOrder = 0
      OnClick = BitBtn1Click
    end
    object BitBtn2: TBitBtn
      AlignWithMargins = True
      Left = 135
      Top = 3
      Width = 117
      Height = 35
      Align = alLeft
      Caption = #1057#1083#1077#1076#1091#1102#1097#1080#1081' '#1087#1072#1082#1077#1090
      TabOrder = 1
      OnClick = BitBtn2Click
    end
    object BitBtn3: TBitBtn
      AlignWithMargins = True
      Left = 644
      Top = 3
      Width = 126
      Height = 35
      Align = alRight
      Caption = #1053#1072#1079#1072#1076' '#1085#1072' 50 '#1084#1089
      TabOrder = 2
      OnClick = BitBtn3Click
    end
    object BitBtn4: TBitBtn
      AlignWithMargins = True
      Left = 776
      Top = 3
      Width = 135
      Height = 35
      Align = alRight
      Caption = #1044#1072#1083#1077#1077' '#1085#1072' 50 '#1084#1089
      TabOrder = 3
      OnClick = BitBtn4Click
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 592
    Width = 914
    Height = 55
    Align = alBottom
    TabOrder = 2
    object GroupBox1: TGroupBox
      AlignWithMargins = True
      Left = 4
      Top = 4
      Width = 185
      Height = 47
      Align = alLeft
      Caption = #1064#1080#1088#1080#1085#1072' '#1089#1087#1077#1082#1090#1088#1072
      TabOrder = 0
      object TrackBar1: TTrackBar
        Left = 2
        Top = 15
        Width = 181
        Height = 30
        Align = alClient
        Max = 1024
        Min = 100
        Position = 1024
        TabOrder = 0
        OnChange = CalculateExecute
      end
    end
    object GroupBox2: TGroupBox
      AlignWithMargins = True
      Left = 195
      Top = 4
      Width = 185
      Height = 47
      Align = alLeft
      Caption = #1071#1088#1082#1086#1089#1090#1100' '#1089#1087#1077#1082#1090#1088#1086#1075#1088#1072#1084#1084#1099
      TabOrder = 1
      object TrackBar2: TTrackBar
        Left = 2
        Top = 15
        Width = 181
        Height = 30
        Align = alClient
        Min = 1
        Position = 5
        TabOrder = 0
        OnChange = CalculateExecute
      end
    end
    object GroupBox3: TGroupBox
      AlignWithMargins = True
      Left = 386
      Top = 4
      Width = 185
      Height = 47
      Align = alLeft
      Caption = #1071#1088#1082#1086#1089#1090#1100' '#1088#1072#1079#1085#1080#1094' '#1087#1086' '#1074#1088#1077#1084#1077#1085#1080
      TabOrder = 2
      Visible = False
      object TrackBar3: TTrackBar
        Left = 2
        Top = 15
        Width = 181
        Height = 30
        Align = alClient
        Min = 1
        Position = 1
        TabOrder = 0
        OnChange = CalculateExecute
      end
    end
    object GroupBox4: TGroupBox
      AlignWithMargins = True
      Left = 577
      Top = 4
      Width = 185
      Height = 47
      Align = alLeft
      Caption = #1055#1086#1076#1089#1074#1077#1090#1082#1072' '#1074#1099#1089#1086#1082#1080#1093' '#1095#1072#1089#1090#1086#1090
      TabOrder = 3
      object TrackBar4: TTrackBar
        Left = 2
        Top = 15
        Width = 181
        Height = 30
        Align = alClient
        Position = 4
        TabOrder = 0
        OnChange = CalculateExecute
      end
    end
  end
  object TabControl1: TTabControl
    Left = 0
    Top = 0
    Width = 914
    Height = 592
    Align = alClient
    TabOrder = 3
    Tabs.Strings = (
      #1047#1074#1091#1082#1086#1074#1086#1081' '#1089#1080#1075#1085#1072#1083
      #1055#1088#1086#1080#1079#1074#1086#1076#1085#1072#1103
      #1042#1090#1086#1088#1072#1103' '#1087#1088#1086#1080#1079#1074#1086#1076#1085#1072#1103)
    TabIndex = 0
    OnChange = TabControl1Change
    ExplicitHeight = 589
    object Image1: TImage
      Left = 4
      Top = 24
      Width = 906
      Height = 367
      Align = alClient
      Stretch = True
      OnMouseMove = Image1MouseMove
      ExplicitLeft = 416
      ExplicitTop = 320
      ExplicitWidth = 105
      ExplicitHeight = 105
    end
    object PaintBox1: TPaintBox
      AlignWithMargins = True
      Left = 7
      Top = 397
      Width = 900
      Height = 188
      Align = alBottom
      OnPaint = PaintBox1Paint
      ExplicitLeft = 3
      ExplicitTop = 456
      ExplicitWidth = 908
    end
    object Splitter1: TSplitter
      Left = 4
      Top = 391
      Width = 906
      Height = 3
      Cursor = crVSplit
      Align = alBottom
      ExplicitLeft = 0
      ExplicitTop = 365
      ExplicitWidth = 914
    end
  end
  object Timer1: TTimer
    Left = 448
    Top = 360
  end
  object ActionList1: TActionList
    Left = 680
    Top = 184
    object Draw: TAction
      Caption = 'Draw'
      OnExecute = DrawExecute
    end
    object Calculate: TAction
      Caption = 'Calculate'
      OnExecute = CalculateExecute
    end
    object DrawGraph: TAction
      Caption = 'DrawGraph'
    end
    object ShowPacket: TAction
      Caption = 'ShowPacket'
      OnExecute = ShowPacketExecute
    end
  end
  object MainMenu1: TMainMenu
    Left = 456
    Top = 368
    object N1: TMenuItem
      Caption = #1057#1075#1083#1072#1078#1080#1074#1072#1085#1080#1077
      object N2: TMenuItem
        AutoCheck = True
        Caption = #1053#1077#1090
        Checked = True
        RadioItem = True
      end
      object N3: TMenuItem
        AutoCheck = True
        Caption = #1053#1086#1088#1084#1072#1083#1100#1085#1086#1077
        RadioItem = True
      end
      object N4: TMenuItem
        AutoCheck = True
        Caption = #1057#1080#1083#1100#1085#1086#1077
        RadioItem = True
      end
    end
  end
end
