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

@WebServlet("/task_2")
public class Task_2 extends HttpServlet {

    String responseTemplate;
	
	@Override
	public void init() throws ServletException
	{
		ServletContext context = getServletContext();
		InputStream is = context.getResourceAsStream("/WEB-INF/src/task_2.html");
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
        String task = req.getParameter("command");
		
		if ( task == null ) {
			makeDefaultResponse(req, resp);
		}		
		else if ( task.equals("cube") ) {
			makeCubeVolumeResponse(req, resp);
		}
		else if ( task.equals("sphere") ) {
			makeSphereVolumeResponse(req, resp);
		}
		else if ( task.equals("parallelepiped") ) {
			makeParallelepipedVolumeResponse(req, resp);
		}
		else if ( task.equals("ellipsoid") ) {
			makeEllipsoidVolumeResponse(req, resp);
		}
		else if ( task.equals("tetra") ) {
			makeTetraVolumeResponse(req, resp);
		}
		else if ( task.equals("tor") ) {
			makeTorVolumeResponse(req, resp);
		}
		else {
			makeDefaultResponse(req, resp);
		}
    }
	
	void makeDefaultResponse(HttpServletRequest req, HttpServletResponse resp) 
		throws ServletException, IOException
	{
		PrintWriter out = resp.getWriter();
		out.printf(responseTemplate, "none", "");
	}
	
	void makeCubeVolumeResponse(HttpServletRequest req, HttpServletResponse resp) 
		throws ServletException, IOException
	{
		PrintWriter out = resp.getWriter();
		String result = "Объём куба: ";
		
		String lengthStr = req.getParameter("length");
		if ( lengthStr == null ) {
			out.printf(responseTemplate, "block; color: darkred",
				"Ошибка! Отсутствует параметр `length`");
			return;
		}
		
		double value = 0;
		try {
			double length = Double.parseDouble(lengthStr);
			value = Math.pow(length, 3);
		}
		catch ( Exception ex ) {
			out.printf(responseTemplate, "block; color: darkred",
				"Ошибка! Не удалось распарсить параметр `length`");
			return;
		}
		
		out.printf(responseTemplate, "block", result + value);
	}
	
	void makeSphereVolumeResponse(HttpServletRequest req, HttpServletResponse resp) 
		throws ServletException, IOException
	{
		PrintWriter out = resp.getWriter();
		String result = "Объём сферы: ";
		
		String radiusStr = req.getParameter("radius");
		if ( radiusStr == null ) {
			out.printf(responseTemplate, "block; color: darkred",
				"Ошибка! Отсутствует параметр `radius`");
			return;
		}
		
		double value = 0;
		try {
			double radius = Double.parseDouble(radiusStr);
			value = 4.0 * Math.PI * Math.pow(radius, 3) / 3.0;
		}
		catch ( Exception ex ) {
			out.printf(responseTemplate, "block; color: darkred",
				"Ошибка! Не удалось распарсить параметр `radius`");
			return;
		}
		
		out.printf(responseTemplate, "block", result + value);
	}
	
	void makeParallelepipedVolumeResponse(HttpServletRequest req, HttpServletResponse resp) 
		throws ServletException, IOException
	{
		PrintWriter out = resp.getWriter();
		String result = "Объём прямоугольного параллелепипеда: ";
		
		String lengthStr = req.getParameter("length");
		if ( lengthStr == null ) {
			out.printf(responseTemplate, "block; color: darkred",
				"Ошибка! Отсутствует параметр `length`");
			return;
		}
		
		String widthStr = req.getParameter("width");
		if ( widthStr == null ) {
			out.printf(responseTemplate, "block; color: darkred",
				"Ошибка! Отсутствует параметр `width`");
			return;
		}
		
		String heightStr = req.getParameter("height");
		if ( heightStr == null ) {
			out.printf(responseTemplate, "block; color: darkred",
				"Ошибка! Отсутствует параметр `height`");
			return;
		}
		
		double value = 0;
		try {
			double length = Double.parseDouble(lengthStr);
			double width = Double.parseDouble(widthStr);
			double height = Double.parseDouble(heightStr);
			
			value = length * width * height;
		}
		catch ( Exception ex ) {
			out.printf(responseTemplate, "block; color: darkred",
				"Ошибка! Не удалось распарсить один из параметров");
			return;
		}
		
		out.printf(responseTemplate, "block", result + value);
	}
	
	void makeEllipsoidVolumeResponse(HttpServletRequest req, HttpServletResponse resp) 
		throws ServletException, IOException
	{
		PrintWriter out = resp.getWriter();
		String result = "Объём эллипсоида: ";
		
		String aStr = req.getParameter("a");
		if ( aStr == null ) {
			out.printf(responseTemplate, "block; color: darkred",
				"Ошибка! Отсутствует параметр `a`");
			return;
		}
		
		String bStr = req.getParameter("b");
		if ( bStr == null ) {
			out.printf(responseTemplate, "block; color: darkred",
				"Ошибка! Отсутствует параметр `b`");
			return;
		}
		
		String cStr = req.getParameter("c");
		if ( cStr == null ) {
			out.printf(responseTemplate, "block; color: darkred",
				"Ошибка! Отсутствует параметр `c`");
			return;
		}
		
		double value = 0;
		try {
			double a = Double.parseDouble(aStr);
			double b = Double.parseDouble(bStr);
			double c = Double.parseDouble(cStr);
			
			value = 4.0 * Math.PI * a * b * c / 3.0;
		}
		catch ( Exception ex ) {
			out.printf(responseTemplate, "block; color: darkred",
				"Ошибка! Не удалось распарсить один из параметров");
			return;
		}
		
		out.printf(responseTemplate, "block", result + value);
	}
	
	void makeTetraVolumeResponse(HttpServletRequest req, HttpServletResponse resp) 
		throws ServletException, IOException
	{
		PrintWriter out = resp.getWriter();
		String result = "Объём тетраэдера: ";
		
		String lengthStr = req.getParameter("length");
		if ( lengthStr == null ) {
			out.printf(responseTemplate, "block; color: darkred",
				"Ошибка! Отсутствует параметр `length`");
			return;
		}
		
		double value = 0;
		try {
			double length = Double.parseDouble(lengthStr);
			value = Math.sqrt(2) * Math.pow(length, 3) / 12.0;
		}
		catch ( Exception ex ) {
			out.printf(responseTemplate, "block; color: darkred",
				"Ошибка! Не удалось распарсить параметр `length`");
			return;
		}
		
		out.printf(responseTemplate, "block", result + value);
	}
	
	void makeTorVolumeResponse(HttpServletRequest req, HttpServletResponse resp) 
		throws ServletException, IOException
	{
		PrintWriter out = resp.getWriter();
		String result = "Объём тора: ";
		
		String rBigStr = req.getParameter("r_big");
		if ( rBigStr == null ) {
			out.printf(responseTemplate, "block; color: darkred",
				"Ошибка! Отсутствует параметр `r_big`");
			return;
		}
		
		String rSmallStr = req.getParameter("r_small");
		if ( rSmallStr == null ) {
			out.printf(responseTemplate, "block; color: darkred",
				"Ошибка! Отсутствует параметр `r_small`");
			return;
		}
		
		double value = 0;
		try {
			double rBig = Double.parseDouble(rBigStr);
			double rSmall = Double.parseDouble(rSmallStr);
			
			value = 2.0 * Math.pow(Math.PI, 2) * rBig * Math.pow(rSmall, 2);
		}
		catch ( Exception ex ) {
			out.printf(responseTemplate, "block; color: darkred",
				"Ошибка! Не удалось распарсить один из параметров");
			return;
		}
		
		out.printf(responseTemplate, "block", result + value);
	}
}
