import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.*;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.stream.Stream;
import java.util.*;
import java.util.stream.Collectors;

@WebServlet("/task_3")
public class Task_3 extends HttpServlet {

    String responseTemplate;
	
	@Override
	public void init() throws ServletException
	{
		ServletContext context = getServletContext();
		InputStream is = context.getResourceAsStream("/WEB-INF/src/task_3.html");
		StringBuilder contentBuilder = new StringBuilder();
		try (Stream<String> stream = new BufferedReader(new InputStreamReader(is, Charset.forName("UTF-8"))).lines())
		{
			stream.forEach(s -> contentBuilder.append(s).append("\n"));
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}
		responseTemplate = contentBuilder.toString();
		log(responseTemplate);
	}

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		req.setCharacterEncoding("UTF-8");
		resp.setContentType("text/html;charset=UTF-8");
		PrintWriter out = resp.getWriter();
		out.printf(responseTemplate, "");
    }
	
	@Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		req.setCharacterEncoding("UTF-8");
		resp.setContentType("text/html;charset=UTF-8");
        
		String numbersStr = req.getParameter("array");
		String[] arrayStrs = numbersStr.split(",");
		
		ArrayList<Integer> array = new ArrayList<Integer>();
		for (String str : arrayStrs) {
			array.add(Integer.parseInt(str));
		}
		Collections.sort(array);
		
		String result = array.stream()
			.map(i -> i.toString())
			.collect(Collectors.joining(","));
		
		PrintWriter out = resp.getWriter();
		out.printf(responseTemplate, result);
	}
}
