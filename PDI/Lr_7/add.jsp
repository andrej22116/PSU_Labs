<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.util.*,java.beans.*,java.io.*" %>
<% request.setCharacterEncoding("UTF-8"); %>
<%! 
	private static final String FILE_PATH = "/db.xml";
	private HashMap<String, Integer> map = new HashMap<String, Integer>();
 %>
 <%
	XMLDecoder decoder;
	try{
		String path = getServletContext().getRealPath("/WebContent");
		decoder = new XMLDecoder(new BufferedInputStream(new FileInputStream(path + FILE_PATH)));
		map = (HashMap<String, Integer>)decoder.readObject();
		decoder.close();
	}catch(FileNotFoundException fileNotFound){
		out.println("Ошибка: Проблемки с файлом db.xml!");
	}
 %>
<!doctype html>
<html>
    <head>
        <meta charset="utf-8">
        <title>Главная</title>
        <link rel="stylesheet" type="text/css" href="style.css">
    </head>
    <body>
		<main>
			<% String product = request.getParameter("product"); %>
			<% String amount = request.getParameter("amount"); %>
			<div class="content" style="display: block;">
				<h1>ПДИ | Лабораторная работа 7 | Вариант 4 </h1>
				<div class="data">
					<table>
						<tr>
							<% if ( map.containsKey(product) ) { %>
							<th colspan="3">Заменить?</th>
							<% } else { %>
							<th colspan="2">Добавить?</th>
							<% } %>
						</tr>
						<tr>
							<th>Товар</th>
							<% if ( map.containsKey(product) ) { %>
							<th>Текущее значение</th>
							<% } %>
							<th>Новое значение</th>
						</tr>
						<tr>
							<th><%= product %></th>
							<% if ( map.containsKey(product) ) { %>
							<td><%= map.get(product) %></td>
							<% } %>
							<td><%= amount %></td>
						</tr>
					</table>
					<div style="display: flex;">
						<form method="post" action="./" class="task-content">
							<input type="hidden" name="product" value="<%= product %>"/>
							<input type="hidden" name="amount" value="<%= amount %>"/>
							<input class="link-btn transition" type="submit" value="Да!">
						</form>
						<form method="get" action="./" class="task-content">
							<input class="link-btn transition" type="submit" value="Нет!">
						</form>
					</div>
					<h6>Выполнил: Стеняев Андрей, студент группы 15-ИТ-1</h6>
				</div>
			</div>
		</main>
    </body>
</html>