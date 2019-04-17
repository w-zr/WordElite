package game.datamodel;

import com.google.gson.Gson;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import game.datamodel.Model.Word;
import game.datamodel.Model.WordReporitory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
public class WordController {
    private final WordReporitory wordReporitory;
    @Autowired
    public WordController(WordReporitory wordReporitory) {
        this.wordReporitory = wordReporitory;
    }

    @PostMapping("/words")
    String addWord(@RequestParam String word) {
        wordReporitory.save(new Word(word));
        return "New word saved.\n";
    }

    @GetMapping("/words")
    String getWord() {
        JsonObject object = new JsonObject();
        JsonArray jsonArray = new JsonParser().parse(new Gson().toJson(wordReporitory.findAll())).getAsJsonArray();
        object.add("words", jsonArray);

        return object.toString();
    }
}
