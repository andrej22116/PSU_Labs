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
 
	if ( request.getMethod().equals("POST") ) {
		String product = request.getParameter("product");
		Integer amount = Integer.parseInt(request.getParameter("amount"));
	
		map.put(product, amount);
		
		XMLEncoder encoder;
		try{
			String path = getServletContext().getRealPath("/WebContent");
			encoder = new XMLEncoder(new BufferedOutputStream(new FileOutputStream(path + FILE_PATH)));
			encoder.writeObject(map);
			encoder.close();
		}catch(FileNotFoundException fileNotFound){
			out.println("Ошибка: Проблемки с файлом db.xml!");
		}
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
			<div class="content">
				<div class="controller">
					<h1>ПДИ | Лабораторная работа 7 | Вариант 4 </h1>
					<form method="get" action="./add.jsp" class="task-content">
						<input name="product" class="input transition" required placeholder="Товар">
						<input name="amount" class="input transition" pattern="\d+" required placeholder="Количество">
						<div>
							<input class="link-btn transition" type="submit" value="Обновить информацию">
						</div>
					</form>
					<h6>Выполнил: Стеняев Андрей, студент группы 15-ИТ-1</h6>
				</div>
				<div class="data">
					<table>
						<tr>
							<th>Товар</th>
							<th>Количество</th>
						</tr>
						<%
							for(Map.Entry<String, Integer> item : map.entrySet()) {
						%>
						<tr><th>
						<% out.println(item.getKey()); %>
						</th><td>
						<% out.println(item.getValue()); %>
						</td></tr>
						<%
							}
						%>
					</table>
				</div>
			</div>
		</main>
    </body>
</html>