<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="MainForm.aspx.cs" Inherits="Lr_3.MainForm" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <asp:Button ID="Gcd2" runat="server" OnClick="Gcd2_Click" Text="НОД 2 числа" />
            <asp:Button ID="Gcd3" runat="server" OnClick="Gcd3_Click" Text="НОД 3 числа" />
            <asp:Button ID="Gcd4" runat="server" OnClick="Gcd4_Click" Text="НОД 4 числа" />
            <br />
            <asp:MultiView ID="MultiView1" runat="server" ActiveViewIndex="0">
                <asp:View ID="View1" runat="server">
                    <br />
                    <asp:Label ID="Gcd2_info" runat="server" Text="НОД для двух чисел"></asp:Label>
                    <br />
                    <br />
                    <asp:TextBox ID="Gcd2Tb1" runat="server"></asp:TextBox>
                    <asp:TextBox ID="Gcd2Tb2" runat="server"></asp:TextBox>
                    <asp:Button ID="CalcGcd2" runat="server" OnClick="CalcGcd2_Click" Text="Расчитать" />
                    &nbsp;
                    <asp:CheckBox ID="Gcd2_fast" runat="server" Text="Использовать быстрый алгоритм" />
                    <br />
                    <asp:Label ID="GcdRes1" runat="server"></asp:Label>
                </asp:View>
                <asp:View ID="View2" runat="server">
                    <br />
                    <asp:Label ID="Gcd3_info" runat="server" Text="НОД для трёх чисел"></asp:Label>
                    <br />
                    <br />
                    <asp:TextBox ID="Gcd3Tb1" runat="server"></asp:TextBox>
                    <asp:TextBox ID="Gcd3Tb2" runat="server"></asp:TextBox>
                    <asp:TextBox ID="Gcd3Tb3" runat="server"></asp:TextBox>
                    <asp:Button ID="CalcGcd3" runat="server" OnClick="CalcGcd3_Click" Text="Расчитать" />
                    &nbsp;
                    <asp:CheckBox ID="Gcd3_fast" runat="server" Text="Использовать быстрый алгоритм" />
                    <br />
                    <asp:Label ID="GcdRes2" runat="server"></asp:Label>
                </asp:View>
                <asp:View ID="View3" runat="server">
                    <br />
                    <asp:Label ID="Gcd4_info" runat="server" Text="НОД для четырёх чисел"></asp:Label>
                    <br />
                    <br />
                    <asp:TextBox ID="Gcd4Tb1" runat="server"></asp:TextBox>
                    <asp:TextBox ID="Gcd4Tb2" runat="server"></asp:TextBox>
                    <asp:TextBox ID="Gcd4Tb3" runat="server"></asp:TextBox>
                    <asp:TextBox ID="Gcd4Tb4" runat="server"></asp:TextBox>
                    <asp:Button ID="CalcGcd4" runat="server" OnClick="CalcGcd4_Click" Text="Расчитать" />
                    &nbsp;&nbsp;
                    <asp:CheckBox ID="Gcd4_fast" runat="server" Text="Использовать быстрый алгоритм" />
                    <br />
                    <asp:Label ID="GcdRes3" runat="server"></asp:Label>
                </asp:View>
            </asp:MultiView>
        </div>
    </form>
</body>
</html>
