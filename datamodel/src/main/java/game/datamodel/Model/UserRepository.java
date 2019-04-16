package game.datamodel.Model;

import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

public interface UserRepository extends CrudRepository<User, Integer> {
    List<User> findAll();

    @Query(value = "update User set exp = ?1, totalPassedStage = ?2 where id = ?3")
    @Modifying
    @Transactional
    void updatePlayer(Integer exp, Integer totalPassedStage, Integer id);

    @Query(value = "update User set numberOfQuestions=?1 where id=?2")
    @Modifying
    @Transactional
    void updateQuestioner(Integer numberOfQuestions, Integer id);
}
