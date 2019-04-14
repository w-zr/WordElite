package game.datamodel.Model;

import lombok.Data;
import javax.persistence.*;

@Data
@Entity
public class User {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;

    private String username;

    private String password;

    public User(){}

    public User(String username, String password) {
        this.username = username;
        this.password = password;
    }
}
