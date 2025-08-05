import io.github.treesitter.jtreesitter.Language;
import PARSER_NS_CLEANED.jtreesitter.LOWER_PARSER_NAME.PARSER_CLASS_NAME;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;

public class PARSER_CLASS_NAMETest {
    @Test
    public void testCanLoadLanguage() {
        assertDoesNotThrow(() -> new Language(PARSER_CLASS_NAME.language()));
    }
}
