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

@WebServlet("/task_1")
public class Task_1 extends HttpServlet {

    String responseTemplate;
	
	@Override
	public void init() throws ServletException
	{
		ServletContext context = getServletContext();
		InputStream is = context.getResourceAsStream("/WEB-INF/src/task_1.html");
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
        String task = req.getParameter("fun");
		String val_t = req.getParameter("val-t");
        double value;
        double delta;
		
		PrintWriter out = resp.getWriter();
		
		try {
			value = Double.parseDouble(req.getParameter("value"));
		}
		catch (Exception ex) {
			log(ex.toString());
			out.printf(responseTemplate, "none", 0.1);
			return;
		}
		
		try {
			delta = Double.parseDouble(req.getParameter("delta"));
		}
		catch (Exception ex) {
			log(ex.toString());
			out.printf(responseTemplate, "none", 0.2);
			return;
		}
		
		if ( task == null || val_t == null ) {
			out.printf(responseTemplate, "none", 0.3);
			return;
		}
		
		double result;
		if ( val_t.equals("deg") ) {
			value *= Math.PI / 180.0; 
		}
		
		double twoPi = Math.PI * 2;
		while ( value > twoPi ) { value -= twoPi; }
		twoPi = -twoPi;
		while ( value < twoPi ) { value -= twoPi; }
		
		if ( task.equals("sin") ) {
			result = calcSin(value, delta);
		}
		else if ( task.equals("cos") ) {
			result = calcCos(value, delta);
		}
		else if ( task.equals("tan") ) {
			result = calcSin(value, delta) / calcCos(value, delta);
		}
		else if ( task.equals("ctan") ) {
			result = calcCos(value, delta) / calcSin(value, delta);
		}
		else {
			throw new IOException();
		}

		out.printf(responseTemplate, "block", result);
    }
	
	double calcSin(double value, double delta)
	{
		double result = 0;
		double iterDelta = 0;
		int iterNum = 0;
		long factorial = 1;
		do {
			iterDelta = Math.pow(-1, iterNum) * Math.pow(value, 2 * iterNum + 1) / factorial;
			result += iterDelta;
			
			iterNum++;
			factorial *= 2 * iterNum;
			factorial *= 2 * iterNum + 1;
		} while ( Math.abs(iterDelta) > delta );
		
		return result;
	}
	
	double calcCos(double value, double delta)
	{
		double result = 0;
		double iterDelta = 0;
		int iterNum = 0;
		long factorial = 1;
		do {
			iterDelta = Math.pow(-1, iterNum) * Math.pow(value, 2 * iterNum) / factorial;
			result += iterDelta;
			
			iterNum++;
			factorial *= (2 * iterNum) - 1;
			factorial *= 2 * iterNum;
		} while ( Math.abs(iterDelta) > delta );
		
		return result;
	}
}
