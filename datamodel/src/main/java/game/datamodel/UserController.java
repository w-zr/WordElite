package game.datamodel;

import com.google.gson.Gson;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import game.datamodel.Model.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
public class UserController {
    private final UserRepository userRepository;

    @Autowired
    public UserController(UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    @PostMapping("/users")
    String addUser(@RequestParam String username, @RequestParam String password) {
        userRepository.save(new User(username, password, 0, 0, 0));
        return "New user saved.\n";
    }

    @GetMapping("/")
    String hello() {
        return "服务器已连接数据库\n";
    }

    @GetMapping("/users")
    String findAllUsers() {
        JsonObject object = new JsonObject();
        JsonArray jsonArray = new JsonParser().parse(new Gson().toJson(userRepository.findAll())).getAsJsonArray();
        object.add("users", jsonArray);

        return object.toString();
    }

    @PutMapping("/players/{id}")
    void updataPlayer(@PathVariable Integer id, @RequestParam Integer exp, @RequestParam Integer totalPassedStage) {
        userRepository.updatePlayer(exp, totalPassedStage, id);
    }

    @PutMapping("/questioners/{id}")
    void updateQuestioner(@PathVariable Integer id, @RequestParam Integer numberOfQuestions) {
        userRepository.updateQuestioner(numberOfQuestions, id);
    }
}